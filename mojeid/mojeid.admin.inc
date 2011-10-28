<?php

/**
 * Menu callback; mojeID admin settings form.
 */
function mojeid_admin_settings($form_state) {
  $form = array();

  $form['mojeid_supress_openid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Supress OpenID'),
    '#description' => t('Suppress general usage of OpenID on this site, only mojeID will be allowed.'),
    '#default_value' => variable_get('mojeid_supress_openid', FALSE),
  );

  $form['mojeid_promo_icons'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Promote mojeID'),
    '#options' => array(
      'user_login_block' => t('User login block'),
      'user_login' => t('User login form'),
      'user_register' => t('User register form'),
      'openid_user_add' => t('OpenID form under user account'),
    ),
    '#default_value' => variable_get('mojeid_promo_icons', array()),
    '#description' => t('Display Powered by mojeID or mojeID Login banners on the checked forms.'),
  );

  if (module_exists('openid_client_ax')) {
    $schema = openid_client_ax_schema_definitions();
    $supported_elements = mojeid_supported_elements();
    foreach ($supported_elements as $uri) {
      if (isset($schema[$uri])) {
        $short_name = openid_client_ax_attribute_name($uri);
        $section = $schema[$uri]['section'];
        $options[$section][$short_name] = $schema[$uri]['label'] . ' <small>(' . $uri . ')</small>';
      }
      else {
        drupal_set_message(t("Element %uri should be supported but it wasn't found in the schema definition.", array('%uri' => $uri)), 'warning');
      }
    }

    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['advanced']['mojeid_required'] = array(
      '#type' => 'fieldset',
      '#title' => t('mojeID required attributes'),
      '#description' => t('Checked mojeID attributes will be required when user is loging-in. Do it only if you really need it.'),
      '#tree' => TRUE
    );

    foreach ($options as $section => $section_options) {
      $form['advanced']['mojeid_required'][] = array(
        '#type' => 'checkboxes',
        '#title' => t('Section @section', array('@section' => $section)),
        '#options' => $section_options,
        '#default_value' => variable_get('mojeid_required', array()),
      );
    }
  }

  return system_settings_form($form);
}

/**
 * Validation handler for the mojeID admin settings form.
 *
 * @see mojeid_admin_settings()
 */
function mojeid_admin_settings_validate($form, &$form_state) {
  if (isset($form_state['values']['mojeid_required']) && is_array($form_state['values']['mojeid_required'])) {
    $flattened = array();
    foreach ($form_state['values']['mojeid_required'] as $section) {
      $flattened += $section;
    }
    $form_state['values']['mojeid_required'] = $flattened;
  }
}
