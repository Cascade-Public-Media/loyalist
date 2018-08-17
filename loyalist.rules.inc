<?php

/**
 * @file
 * Rules API hooks for the Loyalist module.
 */

/**
 * Implements hook_rules_event_info().
 *
 * @see hook_rules_event_info()
 */
function loyalist_rules_event_info() {
  return array(
    'loyalist_new' => array(
      'group' => t('Loyalist'),
      'label' => t('After a visitor is defined as a (new) loyalist.'),
      'module' => 'loyalist',
    ),
    'loyalist_visit' => array(
      'group' => t('Loyalist'),
      'label' => t('Loyalist visits the site.'),
      'module' => 'loyalist',
    ),
  );
}
