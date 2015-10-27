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
  $core_config = config('system.core');

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

    $form['common_settings']['page_title'] = array(
      '#markup' => '<h3>' . 'Custom page title settings' . ':</h3>',
    );
  
  $form['common_settings']['append_site_name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append site name to page title'),
    '#description' => t('Append the site name to the page title. This site name "@site_name".', array('@site_name' => $core_config->get('site_name'))),
    '#default_value' => $config->get('append_site_name'),

  );
  $form['common_settings']['site_name_divider'] = array(
    '#type' => 'textfield',
    '#title' => t('Site name divider'),
    '#default_value' => $config->get('site_name_divider'),
    '#size' => 10,
    '#maxlength' => 10,
    '#description' => t('If the site name is being append, value of this field will be displayed between the page title and the site name.'),
    '#element_validate' => array('base_meta_site_name_divider_validate'),
  );

  $form['common_settings']['actions'] = array('#type' => 'actions');
  $form['common_settings']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  return $form;
}

/**
 * Implements element_validate().
 * 
 */
function base_meta_site_name_divider_validate($element, &$form_state, $form) {
  $append_site_name = $form_state['values']['append_site_name'];
  
  if (empty($element['#value']) && $append_site_name) {
    form_error($element, t('Field "Site name divider" cannot be empty when option "Append site name to page title" is selected.'));
  }
}

/**
 * Implements hook_submit().
 * 
 */
function base_meta_form_submit($form, &$form_state) {
  $config = config('base_meta.settings');

  $config->set('base_canonical_url', trim($form_state['values']['base_canonical_url']));
  $config->set('meta_keywords',      trim($form_state['values']['meta_keywords']));
  $config->set('meta_description',   trim($form_state['values']['meta_description']));
  $config->set('meta_robots',        $form_state['values']['meta_robots']);
  $config->set('append_site_name',   $form_state['values']['append_site_name']);
  $config->set('site_name_divider',  $form_state['values']['site_name_divider']);
  
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
} 