# -*- coding: utf-8 -*-

import sys, os

# -- General configuration -----------------------------------------------------

source_suffix = '.rst'
source_encoding = 'utf-8'
master_doc = 'index'
project = u'HPX API Specification'
copyright = u'2011, Hartmut Kaiser, Bryce Lelbach and others'
version = '0.7'
release = '0.7.0'
today_fmt = '%Y.%m.%d %H.%M.%S'
add_function_parentheses = True
pygments_style = 'sphinx'
show_authors = False

# -- Options for HTML output ---------------------------------------------------

html_theme = 'default'

# -- Options for LaTeX output --------------------------------------------------

latex_documents = [
    ( 'index'
    , 'api.tex'
    , ''
    , 'Hartmut Kaiser, Bryce Lelbach and others'
    , 'manual'
    , False) ]

# -- Epilog for all global substitution ----------------------------------------

rst_epilog = """
.. |ComponentServer| replace:: :ref:`ComponentServer <components_concept_component_server>`
.. |ComponentStub|   replace:: :ref:`ComponentStub <components_concept_component_stub>`
.. |ComponentClient| replace:: :ref:`ComponentClient <components_concept_component_client>`

.. |bsl| replace:: Boost Software License
.. _bsl: http://www.boost.org/LICENSE_1_0.txt
"""

