Loyalist
========

CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Recommended modules
 * Installation
 * Configuration
 * Functionality
 * Limitations
 * Maintainers
 * License

INTRODUCTION
------------

Loyalist uses simple, non-invasive techniques to help site administrators 
identify site "loyalists". By default, a loyalist is defined as a user who 
visits the site three times or more in one week. The number of visits, 
duration, and "cooldown" time between visits can be modified via configuration.

 * For a full description of the module, visit the project page:
   [Loyalist](https://www.drupal.org/project/loyalist)
   
 * To submit bug reports and feature suggestions, or to track changes:
   [Loyalist issues](https://www.drupal.org/project/issues/loyalist)

REQUIREMENTS
------------

No special requirements.

RECOMMENDED MODULES
-------------------

 * [Rules](https://www.drupal.org/project/rules):
   
   When enabled, the Loyalist module provides two new Rules events:
   
   * **After a visitor is defined as a (new) loyalist.**
   
     This event will be dispatched after (or soon after, see LIMITATIONS) a 
     visitor is newly defined as a loyalist.
     
   * **A loyalist visits the site.**
   
     This event will be dispatched when a known loyalist visits the site again.

INSTALLATION
------------

Install as you would normally install a contributed Drupal module. See
[Installing modules](https://www.drupal.org/docs/7/extend/installing-modules)
for further information.

CONFIGURATION
-------------

Configure user permissions in Administration » People » Permissions:

 * Administer Loyalist

   Users need this permission to access and configure the Loyalist module's
   settings.

The site's loyalist definition can be configured from Configuration » People » 
Loyalist.

 * Interval (default: one week)
 
   The amount of time to look at when evaluating the **Number of visits** from 
   a potential loyalist.
   
 * Number of visits (default: 3)
  
   The number of visits by a single site visitor within the **Interval** to 
   qualify the visitor as a loyalist.
   
 * Visit cooldown (default: 30 mins.)
  
   Amount of times between page loads before considering a page load to be a
   new **visit**.

FUNCTIONALITY
-------------

The Loyalist module sets two variables for visitors in a `loyalist` session
array. This array is primarily intended for other module and theme developers
to build from.

  * `loyalist` (integer)
  
    The `loyalist` session variable will be either `0` (not a known loyalist) or 
    `1` (a known loyalist).
    
  * `invoke` (string)
  
    The name of a Rules event that should be invoked. See See RECOMMENDED 
    MODULES for more information .See LIMITATIONS for some additional 
    information about how these Rules events work.

LIMITATIONS
-----------

The Loyalist module uses the Javascript construct 
[LocalStorage](https://developer.mozilla.org/Web/API/Storage/LocalStorage) to 
record and process information about individual users. This module does not 
store any information on the server, personal or otherwise, about visitors. This
is an intentional decision to avoid potential privacy invasive techniques like
fingerprinting.

This approach has a couple of drawbacks that are import to understand:

 * Users can disable or limit access to LocalStorage (e.g. in a private 
   browsing mode). This effectively prevents the Loyalist module from 
   functioning.
   
 * Users can modify LocalStorage data. The functionality of the Loyalist module
   should never be used for things like access to sensitive information or site
   configuration.
   
 * Rules event invocations are delayed. Because loyalist status is determined 
   client-side in Javascript, event invocations for the Rules module are 
   delayed until that status can be communicated to PHP (server-side).
      
MAINTAINERS
-----------

Current maintainers:
 * Christopher Charbonneau Wells (wells) - https://www.drupal.org/u/wells

This project is sponsored by:
 * [Cascade Public Media](https://www.drupal.org/cascade-public-media) for 
 [KCTS9.org](https://kcts9.org/) and [Crosscut.com](https://crosscut.com/).
 
LICENSE
-------

All code in this repository is licensed 
[GPLv2](http://www.gnu.org/licenses/gpl-2.0.html). A LICENSE file is not 
included in this repository per Drupal's module packaging specifications.

See [Licensing on Drupal.org](https://www.drupal.org/about/licensing).
