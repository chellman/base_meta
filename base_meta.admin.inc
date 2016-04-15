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
    '#markup' => '<strong>"Base Meta"</strong> module provides an interface for adding meta tags to pages.'
    . '<br /><strong>Note 1.</strong> Values of meta tags defined below will be added as default to all pages and used for default frontpage.'
    . '<br /><strong>Note 2.</strong> Any tags defined:'
    . '<br />- in tabs "Views pages" or "Taxonomy pages" of this form;'
    . '<br />- in each node via tab "Page title and meta tags" in node edit form – <em>will override defaults.</em>',
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
  
  $form['common_settings']['open_graph'] = array(
    '#type' => 'fieldset',
    '#title' => t('Open Graph'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['common_settings']['open_graph']['meta_og_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Open Graph title'),
    '#default_value' => $config->get('meta_og_title'),
    '#description' => t('The title of this page as rendered on Facebook'),
  );
  
  $form['common_settings']['open_graph']['meta_og_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Open Graph description'),
    '#default_value' => $config->get('meta_og_description'),
    '#rows' => 3,
    '#description' => t('One or two sentence described this page (350 characters max. without any HTML tags.)'),
  );
  
  $form['common_settings']['open_graph']['meta_og_type'] = array(
    '#type' => 'select',
    '#options' => _base_meta_get_og_types(),
    '#title' => t('Open Graph type'),
    '#default_value' => $config->get('meta_og_type'),
    '#description' => t('The type of this item'),
  );
  
  $form['common_settings']['open_graph']['meta_og_image_fid'] = array(
    '#title' => t('Open Graph image'),
    '#description' => t('Upload a custom image'),
    '#type' => 'managed_file',
    '#upload_location' => 'public://' . $config->get('meta_og_image_dir'),
    '#default_value' => $config->get('meta_og_image_fid'),
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
      'file_validate_size' => array(file_upload_max_size()),
    ),
    '#wrapper_attributes' => array(
      'data-editor-image-toggle' => t('Image Upload'),
    ),
  );
  
  $form['common_settings']['open_graph']['meta_og_image_dir'] = array(
    '#title' => t('Image directory'),
    '#type' => 'textfield',
    '#default_value' => $config->get('meta_og_image_dir'),
    '#description' => t('Where images should be uploaded'),
    '#field_prefix' => 'public://',
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
  $config->set('meta_og_title',       trim($form_state['values']['meta_og_title']));
  $config->set('meta_og_description', trim($form_state['values']['meta_og_description']));
  $config->set('meta_og_type',        trim($form_state['values']['meta_og_type']));
  $config->set('meta_og_image_dir',   trim($form_state['values']['meta_og_image_dir']));
  $config->set('meta_og_image_fid',   trim($form_state['values']['meta_og_image_fid']));
  $config->set('append_site_name',   $form_state['values']['append_site_name']);
  $config->set('site_name_divider',  $form_state['values']['site_name_divider']);
  
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
} 

function base_meta_form_views($form, &$form_state) {

  $config = config('base_meta.settings');
  $views_pages = base_meta_get_views_pages();

  $form = array();
  $form['description'] = array(
    '#markup' => 'List of <em>views pages</em> for which you can define page title and meta tags.',
  );

  $form['views_fieldset'] = array(
    '#title' => t("Views pages available"),
    '#type' => 'fieldset',
  );
  
  if (!empty($views_pages)) {
    foreach ($views_pages as $page) {
      foreach ($page as $view_name => $page_path) {
        $form['views_fieldset']['test_' . $view_name] = array(
          
          '#markup' => l($view_name, 'admin/config/search/base_meta/views/' . $view_name, array('attributes' => array('title' => t('Click to edit meta tags for this page.')))). '<br />',
        );
      }
    }
  }
  else {
    $form['views_fieldset']['empty'] = array(
      '#markup' => t('Sorry, you have not non-admin views with display of type "Page"'),
    );
  }
  
  return $form;
}

function base_meta_form_taxonomy($form, &$form_state) {

  $config = config('base_meta.settings');
  $vocabularies = array('-' => t('Please select'));
  $vocs = taxonomy_get_vocabularies();
  foreach ($vocs as $m_name => $v_obj) {
    $vocabularies[$m_name] = $v_obj->name;
  }
  
  $form = array();
  $form['description'] = array(
    '#markup' => 'List of <em>taxonomy pages</em> for which you can define page title and meta tags.',
  );
  
  $selected = !empty($form_state['values']['terms_select']) ? $form_state['values']['terms_select'] : key($vocabularies);

  $form['terms_select'] = array(
    '#title' => t('Select vocabulary name'),
    '#type' => 'select',
    '#options' => $vocabularies,
    '#default_value' => $selected,
    '#ajax' => array(
      'callback' => 'base_meta_taxonomy_callback',
      'wrapper' => 'terms-div',
      'method' => 'replaceWith',
      'effect' => 'slide',
      'progress' => array('type' => 'none'),
    ),
  );

  $form['terms_fieldset'] = array(
    '#title' => t("Terms Available"),
    '#prefix' => '<div id="terms-div">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
  );

  if ($selected != '-') {

    $terms = taxonomy_get_tree($selected);
    
    if (!empty($terms)) {
      
      foreach ($terms as $key => $term_obj) {
        
        $form['terms_fieldset'][$key][$selected] = array(

          '#markup' => l($term_obj->name, 'admin/config/search/base_meta/taxonomy/' . $term_obj->name, array('attributes' => array('title' => t('Click to edit meta tags for this page.')))). '<br />',
        );
      }  
    }
    else {
      $form['terms_fieldset'][$selected] = array(
        '#markup' => t('Terms not found.'),
      );
    }
    
  }
  else {
    $form['terms_fieldset'][$selected] = array(
      '#markup' => t('Terms not found.'),
    );
  }
  

  return $form;
}

/**
 * Callback for taxonomy.
 *
 * @return array
 *   Renderable array (the taxonomy fieldset)
 */
function base_meta_taxonomy_callback($form, $form_state) {
  return $form['terms_fieldset'];
}


/**
 * Edit form for views and taxonomy pages 
 * 
 * @param type $form
 * @param type $form_state
 */
function base_meta_custom_tags_edit($form, &$form_state) {

  $args      = arg();
  $page_type = $args[4];
  $page_name = $args[5];
  
  $saved_tags = base_meta_get_tags_from_config_file($page_type, $page_name);

  $form_state['page_info'] = array(
    'type' => $page_type,
    'name' => $page_name,
  ); 
  $form['base_meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page title and meta tags'),
    '#access' => user_access('edit base meta tags'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // @todo: add link to corresponded page
  $form['base_meta']['define'] = array(
    '#markup' => t("Values for <em>'$page_type page'</em> named <em>'$page_name'</em>"),
  );

  $form['base_meta']['page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => isset($saved_tags['page_title']) ? $saved_tags['page_title'] : '',
    '#description' => t('Description of this page to appear in the &lt;title&gt; tag for search engines search result listings.'),
  );

  $form['base_meta']['meta_keywords'] = array(
    '#type' => 'textfield',
    '#title' => t('Meta keywords'),
    '#default_value' => isset($saved_tags['meta_keywords']) ? $saved_tags['meta_keywords'] : '',
    '#size' => 120,
    '#maxlength' => 255,
    '#description' => t('Comma separated list of keywords.'),
  );

  $form['base_meta']['meta_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Meta description'),
    '#default_value' => isset($saved_tags['meta_description']) ? $saved_tags['meta_description'] : '',
    '#rows' => 3,
    '#description' => t('One or two sentence described this page (350 characters max. without any HTML tags.)'),
  );

  $form['base_meta']['meta_robots'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Meta robots'),
    '#options' => backdrop_map_assoc(array('NOINDEX', 'NOFOLLOW', 'NOARCHIVE', 'NOODP', 'NOSNIPPET')),
    '#default_value' => isset($saved_tags['meta_robots']) ? $saved_tags['meta_robots'] : array(),
    '#description' => 'Search engines assume "INDEX" and "FOLLOW" unless these are specifically disabled above.',
  );
  $form['base_meta']['meta_canonical'] = array(
    '#type' => 'textfield',
    '#title' => t('Canonical URL'),
    '#default_value' => isset($saved_tags['meta_canonical']) ? $saved_tags['meta_canonical'] : '',
    '#description' => t("Use a relative URL without the initial slash for this (or default) domain or full URL in other case."
      . " By default (if no value) this will automatically use URL of this page."),
  );

  $form['base_meta']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function base_meta_custom_tags_edit_validate($form, &$form_state) {
  $base_meta_values = $form_state['values'];

  $empty_tags = (
      empty($base_meta_values['page_title']) &&
      empty($base_meta_values['meta_keywords']) &&
      empty($base_meta_values['meta_description']) &&
      empty($base_meta_values['meta_canonical'])) ? TRUE : FALSE;

  $checked_boxes = FALSE;

  foreach ($base_meta_values['meta_robots'] as $tag => $value) {
    if (is_string($value)) {
      $checked_boxes = TRUE;
    }
  }

  if ($empty_tags && !$checked_boxes) {
    form_set_error('', t('You must fill some values to the fields, nothing to save!'));
  }
}

/**
 * Implements hook_submit().
 * 
 */
function base_meta_custom_tags_edit_submit($form, &$form_state) {
  
  $config          = config('base_meta.settings');
  $page_type       = $form_state['page_info']['type'];
  $page_name       = $form_state['page_info']['name'];
  $config_sub_path = $page_type . '_pages_meta_tags.' . $page_name . '.';

  $config->set($config_sub_path . 'page_title',       trim($form_state['values']['page_title']));
  $config->set($config_sub_path . 'meta_keywords',    trim($form_state['values']['meta_keywords']));
  $config->set($config_sub_path . 'meta_description', trim($form_state['values']['meta_description']));
  $config->set($config_sub_path . 'meta_robots',      $form_state['values']['meta_robots']);
  $config->set($config_sub_path . 'meta_canonical',   trim($form_state['values']['meta_canonical']));
  
  $config->save();
  backdrop_set_message(t('Tags for page have been saved.'));
}