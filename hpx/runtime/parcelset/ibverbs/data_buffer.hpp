//  Copyright (c)      2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_IBVERBS_DATA_BUFFER_HPP)
#define HPX_PARCELSET_IBVERBS_DATA_BUFFER_HPP

namespace hpx { namespace parcelset { namespace ibverbs
{
    struct data_buffer
        : boost::noncopyable
    {

        static const std::size_t mr_buffer_offset = 2 * sizeof(boost::uint64_t);

        data_buffer()
          : zero_copy_(true)
          , mr_buffer_(0)
          , mr_buffer_size_(0)
          , size_(0)
        {}

        void set_mr_buffer(char * mr_buffer, std::size_t mr_buffer_size)
        {
            mr_buffer_ = mr_buffer + mr_buffer_offset;
            mr_buffer_size_ = mr_buffer_size - mr_buffer_offset;
        }

        std::size_t capacity() const
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                return mr_buffer_size_;
            }
            else
            {
                return data_.capacity();
            }
        }

        std::size_t size() const
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                return size_;
            }
            else
            {
                return data_.size();
            }
        }

        void reserve(std::size_t size)
        {
            
            if(size < mr_buffer_size_)
            {
                BOOST_ASSERT(mr_buffer_);
                if(zero_copy_ == false)
                {
                    if(data_.size() > 0)
                    {
                        std::memcpy(
                            mr_buffer_
                          , &data_[0]
                          , data_.size()
                        );
                        data_.clear();
                    }
                    zero_copy_ = true;
                }
            }
            else
            {
                data_.reserve(size);
                if(zero_copy_ == true)
                {
                    if(size_ > 0)
                    {
                        data_.resize(size_);
                        
                        std::memcpy(
                            &data_[0]
                          , mr_buffer_
                          , size_
                        );

                        size_ = 0;
                    }
                    zero_copy_ = false;
                }
            }
        }

        void resize(std::size_t size)
        {
            if(size < mr_buffer_size_)
            {
                BOOST_ASSERT(mr_buffer_);
                if(zero_copy_ == false)
                {
                    if(data_.size() > 0)
                    {
                        std::memcpy(
                            mr_buffer_
                          , &data_[0]
                          , data_.size()
                        );
                        data_.clear();
                    }
                    zero_copy_ = true;
                }
                size_ = size;
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
            }
            else
            {
                data_.resize(size);
                if(zero_copy_ == true)
                {
                    BOOST_ASSERT(mr_buffer_);
                    BOOST_ASSERT(size_ < mr_buffer_size_);
                    if(size_ > 0)
                    {
                        std::memcpy(
                            &data_[0]
                          , mr_buffer_
                          , size_
                        );
                        size_ = 0;
                    }
                    zero_copy_ = false;
                }
            }
        }

        char * data()
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return mr_buffer_;
            }
            else
            {
                return data_.data();
            }
        }

        const char * data() const
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return mr_buffer_;
            }
            else
            {
                return data_.data();
            }
        }

        char & operator[](std::size_t idx)
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(idx < mr_buffer_size_);
                BOOST_ASSERT(idx < size_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return *(mr_buffer_ + idx);
            }
            else
            {
                return data_[idx];
            }
        }

        char const & operator[](std::size_t idx) const
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(idx < mr_buffer_size_);
                BOOST_ASSERT(idx < size_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return *(mr_buffer_ + idx);
            }
            else
            {
                return data_[idx];
            }
        }

        char * begin()
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return mr_buffer_;
            }
            else
            {
                return &data_[0];
            }
        }

        const char * begin() const
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return mr_buffer_;
            }
            else
            {
                return &data_[0];
            }
        }

        char * end()
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return mr_buffer_ + size_;
            }
            else
            {
                return &data_[0] + data_.size();
            }
        }

        const char * end() const
        {
            if(zero_copy_)
            {
                BOOST_ASSERT(mr_buffer_);
                BOOST_ASSERT(size_ < mr_buffer_size_);
                BOOST_ASSERT(size_ > 0);
                return mr_buffer_ + size_;
            }
            else
            {
                return &data_[0] + data_.size();
            }
        }

        void clear()
        {
            zero_copy_ = true;
            size_ = 0;

            data_.clear();
        }

        bool zero_copy_;
        std::vector<char> data_;
        char * mr_buffer_;
        std::size_t mr_buffer_size_;
        std::size_t size_;
    };
}}}

#endif

