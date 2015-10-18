<?php

/**
 * @file
 * Admin form to add base meta tags
 *
 */

/**
 * 
 * Administration form for base meta tags management.
 *
 * @return Form for administering module.
 */
function base_meta_form() {

  $config = config('base_meta.settings');

  $form = array();
  $form['description'] = array(
    '#prefix' => '<div>',
    '#markup' => '<strong>"Base Meta Tags"</strong> module provides an interface for adding basic set of meta tags.'
    . '<br /><strong>Note:</strong> values of meta tags defined below will be added as default to all pages and used for default frontpage.'
    . '<br /><strong>Note 2:</strong> any tags defined for each page via special tab in node edit form <em>will override defaults</em>.',
    '#suffix' => '</div>',
  );
  $form['common_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default meta tags values'),
  );
  $form['common_settings']['base_canonical_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base Canonical URL'),
    '#default_value' => $config->get('base_canonical_url'),
    '#size' => 70,
    '#maxlength' => 255,
    '#description' => t('This will be used as "Base URL" for any canonical URL on this site.'),
  );
  $form['common_settings']['meta_keywords'] = array(
    '#type' => 'textfield',
    '#title' => t('Keywords'),
    '#default_value' => $config->get('meta_keywords'),
    '#size' => 70,
    '#maxlength' => 255,
    '#description' => t('Comma separated list of keywords.'),
  );
  $form['common_settings']['meta_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $config->get('meta_description'),
    '#rows' => 3,
    '#cols' => 30,
    '#description' => t('One or two sentence described the page.'),
  );

  $form['common_settings']['meta_robots'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Robots'),
    '#options' => backdrop_map_assoc(array('NOINDEX', 'NOFOLLOW', 'NOARCHIVE', 'NOODP', 'NOSNIPPET')),
    '#default_value' => $config->get('meta_robots'),
    '#description' => 'Search engines assume "INDEX" and "FOLLOW" unless these are specifically disabled above.',
  );


  $form['common_settings']['actions'] = array('#type' => 'actions');
  $form['common_settings']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  return $form;
}

function base_meta_form_submit($form, &$form_state) {
  $config = config('base_meta.settings');

  $config->set('base_canonical_url', trim($form_state['values']['base_canonical_url']));
  $config->set('meta_keywords', trim($form_state['values']['meta_keywords']));
  $config->set('meta_description', trim($form_state['values']['meta_description']));
  $config->set('meta_robots', $form_state['values']['meta_robots']);

  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
