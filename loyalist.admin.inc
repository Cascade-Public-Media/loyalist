<?php

/**
 * @file
 * Admin form functions for the Loyalist module.
 */

/**
 * Loyalist settings.
 *
 * @return array
 *   System settings form render array.
 */
function loyalist_settings() {
  $cooldown_setting = variable_get('loyalist_cooldown');
  $interval_setting = variable_get('loyalist_interval');
  $visits_setting = variable_get('loyalist_visits');

  $form = array();

  $form['help'] = array(
    '#type' => 'html_tag',
    '#tag' => 'p',
    '#value' => t('The settings below define a <em>loyalist</em> in the
      context of this site. Currently, a loyalist is defined as any site visitor
      who visits <strong>@visits times</strong> in <strong>@interval</strong> 
      with a <strong>@cooldown cooldown</strong> period between visits.',
      array(
        '@cooldown' => format_interval($cooldown_setting),
        '@interval' => format_interval($interval_setting),
        '@visits' => $visits_setting,
      )
    ),
  );

  $intervals = array(
    86400, 86400 * 2, 86400 * 3, 86400 * 4, 86400 * 5, 86400 * 6,
    604800, 604800 * 2, 604800 * 3,
    2592000, 2592000 * 2, 2592000 * 3, 2592000 * 4, 2592000 * 5, 2592000 * 6,
    31536000,
  );
  $options = array();
  foreach ($intervals as $interval) {
    $options[$interval] = format_interval($interval);
  }

  $form['loyalist_interval'] = array(
    '#type' => 'select',
    '#title' => t('Interval'),
    '#description' => t('The amount of time to look at when evaluating the
      <strong>Number of visits</strong> from a potential loyalist.'),
    '#default_value' => $interval_setting,
    '#options' => $options,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['loyalist_visits'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of visits'),
    '#description' => t('The number of visits by a single site visitor within
      the <strong>Interval</strong> to qualify the visitor as a loyalist.'),
    '#default_value' => $visits_setting,
    '#attributes' => array(
      'size' => 10,
    ),
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $intervals = array(
    60 * 5, 60 * 10, 60 * 15, 60 * 30,
    3600, 3600 * 2, 3600 * 3, 3600 * 4, 3600 * 5, 3600 * 6, 3600 * 12,
    86400, 86400 * 2, 86400 * 3, 86400 * 4, 86400 * 5, 86400 * 6,
    604800,
  );
  $options = array();
  foreach ($intervals as $interval) {
    $options[$interval] = format_interval($interval);
  }

  $form['loyalist_cooldown'] = array(
    '#type' => 'select',
    '#title' => t('Visit cooldown'),
    '#description' => t('Amount of times between page loads before
      considering a page load to be a new <strong>visit</strong>.'),
    '#default_value' => $cooldown_setting,
    '#options' => $options,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return system_settings_form($form);
}
