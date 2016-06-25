//  include_check implementation  --------------------------------------------//

//  Copyright Beman Dawes   2002.
//  Copyright Gennaro Prota 2006.
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm>

#include "include_check.hpp"
#include "boost/regex.hpp"
#include "boost/lexical_cast.hpp"
#include "function_hyper.hpp"

namespace boost
{
  namespace inspect
  {
    boost::regex include_regex(
      "^\\s*#\\s*include\\s*<([^\n>]*)>(\\s|//[^\\n]*|/\\*.*?\\*/)*$"     // # include <foobar>
      "|"
      "^\\s*#\\s*include\\s*\"([^\n\"]*)\"(\\s|//[^\\n]*|/\\*.*?\\*/)*$"  // # include "foobar"
      , boost::regex::normal);

    names_includes const names[] =
    {
      { "(\\bstd\\s*::\\s*make_shared\\b)", "std::make_shared", "memory" },
      { "(\\bstd\\s*::\\s*((map)|(set))\\b)", "std::\\2", "\\2" },
      { "(\\bstd\\s*::\\s*(multi((map)|(set)))\\b)", "std::\\2", "\\3" },
      { "(\\bstd\\s*::\\s*((shared|unique)_ptr)\\b)", "std::\\2", "memory" },
      { "(\\bstd\\s*::\\s*(unordered_((map|set)))\\b)", "std::\\2", "unordered_\\3" },
      { "(\\bstd\\s*::\\s*(unordered_multi((map)|(set)))\\b)", "std::\\2", "unordered_\\3" },
      { "(\\bstd\\s*::\\s*list\\b)", "std::list", "list" },
      { "(\\bstd\\s*::\\s*string\\b)", "std::string", "string" },
      { "(\\bstd\\s*::\\s*vector\\b)", "std::vector", "vector" },
      { "(\\bstd\\s*::\\s*(mem((set)|(cpy)|(move)))\\b)", "std::\\2", "cstring" },
      { "(\\bboost\\s*::\\s*atomic\\b)", "boost::atomic", "boost/atomic.hpp" },
      { "(\\bboost\\s*::\\s*(((exception)|(intrusive))_ptr)\\b)", "boost::\\3_ptr", "boost/\\3_ptr.hpp" },
      { nullptr, nullptr, nullptr }
    };

    //  include_check constructor  -------------------------------------------//

    include_check::include_check()
      : m_errors(0)
    {
      // C/C++ source code...
      register_signature( ".c" );
      register_signature( ".cpp" );
      register_signature( ".cxx" );
      register_signature( ".h" );
      register_signature( ".hpp" );
      register_signature( ".hxx" );
      register_signature( ".inc" );
      register_signature( ".ipp" );

      for (names_includes const* names_it = &names[0];
           names_it->name_regex != nullptr;
           ++names_it)
      {
        std::string rx(names_it->name_regex);
        rx +=
          "|"                   // or (ignored)
          "("
          "//[^\\n]*"           // single line comments (//)
          "|"
          "/\\*.*?\\*/"         // multi line comments (/**/)
          "|"
          "\"([^\"\\\\]|\\\\.)*\"" // string literals
          ")";
        regex_data.push_back(names_regex_data(names_it, rx));
      }
    }

    //  inspect ( C++ source files )  ---------------------------------------//

    void include_check::inspect(
      const string & library_name,
      const path & full_path,      // example: c:/foo/boost/filesystem/path.hpp
      const string & contents)     // contents of file to be inspected
    {
      if (contents.find( "hpxinspect:" "noinclude" ) != string::npos) return;

      // first, collect all #includes in this file
      std::set<std::string> includes;

      boost::sregex_iterator cur(contents.begin(), contents.end(), include_regex), end;

      for( ; cur != end; ++cur /*, ++m_errors*/ )
      {
        auto m = *cur;
        if (m[1].matched)
          includes.insert(std::string(m[1].first, m[1].second));
        else if (m[2].matched)
          includes.insert(std::string(m[2].first, m[2].second));
      }

      // for all given names, check whether corresponding include was found
      std::set<std::string> checked_includes;
      std::set<std::string> found_names;
      for (names_regex_data const& d : regex_data)
      {
        boost::sregex_iterator cur(contents.begin(), contents.end(), d.pattern), end;
        for(/**/; cur != end; ++cur)
        {
          auto m = *cur;
          if (m[1].matched)
          {
            // avoid checking the same include twice
            auto checked_includes_it =
                checked_includes.find(m.format(d.data->include));
            if (checked_includes_it != checked_includes.end())
               continue;

            // avoid errors to be reported twice
            std::string found_name(m[1].first, m[1].second);
            if (found_names.find(found_name) != found_names.end())
                continue;
            found_names.insert(found_name);

            auto include_it = includes.find(m.format(d.data->include));
            if (include_it == includes.end())
            {
              // include is missing
              auto it = contents.begin();
              auto match_it = m[1].first;
              auto line_start = it;

              string::size_type line_number = 1;
              for (/**/; it != match_it; ++it)
              {
                if (string::traits_type::eq(*it, '\n'))
                {
                  ++line_number;
                  line_start = it + 1; // could be end()
                }
              }

              ++m_errors;
              error(library_name, full_path, string(name())
                  + " missing #include ("
                  + m.format(d.data->include)
                  + ") for symbol "
                  + m.format(d.data->name) + " on line "
                  + linelink(full_path, boost::lexical_cast<string>(line_number)));
            }
            checked_includes.insert(m.format(d.data->include));
          }
        }
      }
    }

  } // namespace inspect
} // namespace boost

