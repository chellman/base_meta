Base Meta: Page Title And Meta Tags
===================================

The Base Meta module allows you define page title tag and meta tags 
for search engines:

 - for each page provided by node, views or taxonomy term you can set
   page title tag instead used by default;
 - keywords, descriptions and robots tags - you can set on per page/node 
   basis or as defaults for all pages where meta tags not exactly defined;
 - for each page you can re-define canonical URL;

 - you can set different base URL for using in all canonical URLs 
   instead default (actual) site domain.

Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules

- Visit the configuration page under Administration > Configuration > 
  Search and metadata > Base Meta module settings (admin/config/search/base_meta) 
  if you need set default values.

Usage
-----
 - any node Create/Edit form received additional topmost vertical tab named 
   'Page title and meta tags' - checkbox 'Define tags for page of this node'
   allow you to fill opened fields as required;
 - meta tags for pages provided by module`taxonomy` can be set by using tab
   in admin area: Administration > Configuration > Search and metadata > 
   Base Meta module settings > Taxonomy pages or visit URL
   <your_domain_name>/admin/config/search/base_meta/taxonomy,
   then select vocabulary which contain terms needed, select any available 
   term name for opening add/edit meta tags form; 
 - meta tags for pages provided by module `views` can be set by using tab
   in admin area: Administration > Configuration > Search and metadata > 
   Base Meta module settings > Views pages or visit URL
   <your_domain_name>/admin/config/search/base_meta/views
   and select any available page name for opening add/edit meta tags form.  

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainer
------------------

- Vladimir (https://github.com/findlabnet/)

Credits and motivation
----------------------

- Inspired by projects "Metatag" and "Page Title" in the quest for simplicity.

- Some people cannot adopt CMS without such (even very basic) functionality.