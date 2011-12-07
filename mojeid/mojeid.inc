<?php


//=============================================================================
//  MENU CALLBACKS
//=============================================================================


/**
 * Menu callback returns XRDC.XML with domain URI
 *
 * Or alternatively we could use xrds_simple.module
 */
function mojeid_xrds_page() {
  drupal_add_http_header('Content-Type', 'application/xml; utf-8');
  print "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<xrds:XRDS xmlns:xrds=\"xri://\$xrds\" xmlns=\"xri://\$xrd*(\$v*2.0)\">
  <XRD>
    <Service>
      <Type>http://specs.openid.net/auth/2.0/return_to</Type>
      <URI>" . url('', array('absolute' => TRUE)) . "</URI>
    </Service>
  </XRD>
</xrds:XRDS>";
  exit();
}


//=============================================================================
//  FORMS AND FORM HANDLERS
//=============================================================================


/**
 * Implementation of hook_form_alter().
 *
 * Adds OpenID selector to the OpenID forms.
 */
function _mojeid_form_alter(&$form, &$form_state, $form_id) {
  global $language;
  $module_path = drupal_get_path('module', 'mojeid');
  $supress_openid = variable_get('mojeid_supress_openid', FALSE);

  // load additional CSS and JS on these forms
  if (in_array($form_id, array('user_login_block', 'user_login', 'openid_user_add'))) {
    $form['#attached']['css'][] = $module_path . '/mojeid.css';
    $form['#attached']['js'][] = $module_path . '/mojeid.js';
  }

  if (in_array($form_id, array('user_login_block', 'user_login'))) {
    $meta_xrds = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'x-xrds-location',
        'content' => url('openid/xrds.xml', array('absolute' => TRUE)),
      ),
    );
    drupal_add_html_head($meta_xrds, 'mojeid_xrds_location');

    if (!empty($form_state['input']['mojeid_identifier'])) {
      $form['name']['#required'] = FALSE;
      $form['pass']['#required'] = FALSE;
      unset($form['#submit']);
      $form['#validate'] = array('mojeid_login_validate');
    }

    $form['mojeid_identifier'] = array(
      '#type' => 'textfield',
      '#title' => t('Log in using mojeID'),
      '#size' => ($form_id == 'user_login') ? 38 : 8,
      '#field_suffix' => t('.mojeID.cz'),
      '#maxlength' => 255,
      '#weight' => -1,
      '#description' => l(t('What is mojeID?'), 'http://www.mojeid.cz/page/805/', array('external' => TRUE)) . " " . l(t('Create new MojeID account'), 'http://www.mojeid.cz/page/795/', array('external' => TRUE)),
    );

    if ($supress_openid) {
      $form['openid_identifier']['#type'] = 'hidden';
    }

    $items = array();
    $items[] = array(
      'data' => l(t('Log in using mojeID'), '#mojeid-login', array('external' => TRUE)),
      'class' => array('mojeid-link'),
    );

    if (!$supress_openid) {
      $items[] = array(
        'data' => l(t('Log in using OpenID'), '#openid-login', array('external' => TRUE)),
        'class' => array('openid-link'),
      );
      $items[] = array(
        'data' => l(t('Cancel OpenID login'), '#', array('external' => TRUE)),
        'class' => array('user-link'),
      );
    }

    $items[] = array(
      'data' => l(t('Cancel mojeID login'), '#', array('external' => TRUE)),
      'class' => array('mojeid-user-link'),
    );

    $form['openid_links'] = array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#attributes' => array('class' => array('openid-links')),
      '#weight' => 1,
    );

    if (_mojeid_promo_icon_display($form_id)) {
      if ($icon = mojeid_file_language_variant($module_path . '/img/mojeid_log-in.png')) {
        $form['mojeid_img'] = array(
          '#markup' => theme('image', array('path' => $icon, 'alt' => t('mojeID.cz'), 'title' => t('Supports mojeID authentication'), 'attributes' => array('class' => 'mojeid-login-img'))),
          '#weight' => ($form_id == 'user_login_block') ? 5 : 3,
        );
      }
    }

  }
  elseif ($form_id == 'user_register') {

    if (isset($_SESSION['openid']['values']) && mojeid_openid_is_mojeid($_SESSION['openid']['values']['auth_openid'])) {
      $form['openid_display']['#title'] = t('Your MojeID');
      $form['openid_display']['#description'] = t('This MojeID will be attached to your account after registration.');
    }

    if (_mojeid_promo_icon_display($form_id)) {
      if ($icon = mojeid_file_language_variant($module_path . '/img/mojeid_log-in.png')) {
        $image = theme('image', array('path' => $icon, 'alt' => t('mojeID.cz'), 'title' => t('Supports mojeID authentication'), 'attributes' => array('class' => 'mojeid-login-img')));
        $form['account']['mojeid_img'] = array(
          '#markup' => l($image, 'user', array('html' => TRUE, 'fragment' => 'mojeid')),
          '#weight' => 1,
        );
      }
    }

  }
  elseif ($form_id == 'openid_user_add') {

    if (!empty($form_state['input']['mojeid_identifier'])) {
      $form['#validate'] = array('mojeid_openid_user_add_validate');
      $form['#submit'] = array('mojeid_openid_user_add_submit');
    }

    if ($supress_openid) {
      $form['openid_identifier']['#type'] = 'hidden';
    }

    if (_mojeid_promo_icon_display($form_id)) {
      if ($icon = mojeid_file_language_variant($module_path . '/img/mojeid_powered.png')) {
        $form['mojeid_img'] = array(
          '#markup' => theme('image', array('path' => $icon, 'alt' => t('mojeID.cz'), 'title' => t('Supports MojeID authentication'), 'attributes' => array('class' => 'mojeid-login-img'))),
          '#weight' => -10,
        );
      }
    }

    $form['mojeid_identifier'] = array(
      '#type' => 'textfield',
      '#title' => t('mojeID'),
      '#size' => 38,
      '#field_suffix' => t('.mojeID.cz'),
      '#maxlength' => 255,
      '#weight' => -1,
      '#description' => l(t('Why mojeID?'), 'http://www.mojeid.cz/page/805/', array('external' => TRUE)) . " " . l(t('Create new mojeID account'), 'http://www.mojeid.cz/page/795/', array('external' => TRUE)) . '.',
    );
  }
}

/**
 * Login form_validate handler; overrides openid_login_validate().
 */
function mojeid_login_validate($form, &$form_state) {
  $return_to = $form_state['values']['openid.return_to'];
  if (empty($return_to)) {
    $return_to = url('', array('absolute' => TRUE));
  }

  // Normalize the input - be nice if someone insert mojeid.cz as a part of the claimed id.
  $mojeid = trim(str_ireplace('.mojeid.cz', '', $form_state['values']['mojeid_identifier']));
  $mojeid = $mojeid . '.mojeid.cz';
  openid_begin($mojeid, $return_to, $form_state['values']);

  // assign OpenID errors to the MojeID field
  _mojeid_repair_form_errors($form_state);
}

/**
 * Handle openid/mojeid errors in mojeid forms
 */
function _mojeid_repair_form_errors($form_state) {
  $form_errors = form_get_errors();
  if (isset($form_errors['openid_identifier']) && !empty($form_state['values']['mojeid_identifier'])) {
    $messages = drupal_get_messages('error', FALSE);
    $openid_error = $form_errors['openid_identifier'];

    // clear error messages
    drupal_get_messages('error', TRUE);
    $idx = array_search($openid_error, $messages['error']);
    unset($messages['error'][$idx]);
    foreach ($messages['error'] as $msg) {
      // re-add all messages
      drupal_set_message('error', $msg);
    }
    // set MojeID error
    $openid_error = t('Sorry, that is not a valid MojeID. Please ensure you have spelled your ID correctly.');
    form_set_error('mojeid_identifier', $openid_error, TRUE);
  }
}

/**
 * Openid add form_validate handler; overrides user_add_validate().
 */
function mojeid_openid_user_add_validate($form, &$form_state) {
  $form_state['values']['openid_identifier'] = $form_state['values']['mojeid_identifier'] . '.mojeid.cz';
  // Check for existing entries.
  $claimed_id = openid_normalize($form_state['values']['openid_identifier']);
  if (db_query("SELECT authname FROM {authmap} WHERE authname = :authname", (array(':authname' => $claimed_id)))->fetchField()) {
    form_set_error('mojeid_identifier', t('That OpenID is already in use on this site.'));
  }
}

/**
 * Openid add form_submit handler; overrides user_add_submit().
 */
function mojeid_openid_user_add_submit($form, &$form_state) {
  $form_state['values']['openid_identifier'] = $form_state['values']['mojeid_identifier'] . '.mojeid.cz';
  $return_to = url('user/' . arg(1) . '/openid', array('absolute' => TRUE));
  openid_begin($form_state['values']['openid_identifier'], $return_to);
  _mojeid_repair_form_errors($form_state);
}


//=============================================================================
//  MODULE FUNCTIONS
//=============================================================================


function mojeid_openid_is_mojeid($openid) {
  return (strcmp('.mojeid.cz', substr(trim($openid, " /"), -10)) == 0) ? TRUE : FALSE;
}

/**
 * Checks if the element is from the set of mojeID's supported elements.
 *
 * @param string $uri
 */
function mojeid_is_supported_element($uri) {
  $elements = mojeid_supported_elements();
  return in_array($uri, $elements);
}

/**
 * Checks if file exists for given language variant. It searches for files with
 * ISO-2 langcode injected before file extension.
 *
 * Example:
 *   "mojeid_icon.jpg" returns "mojeid_icon.cs.jpg" if Czech is given language
 *
 * @param string $file
 * @param object $language
 *   Optional Drupal language object, defaults to current global language
 *
 * @return string|FALSE
 *   A filepath to language based file variant or original file or FALSE if no file exists
 */
function mojeid_file_language_variant($file, $language = NULL) {
  $return = $lang_file = FALSE;

  if (is_null($language)) {
    $language = $GLOBALS['language'];
  }

  // try if file filename.<ISO-2-LANGCODE>.ext exists
  $start = strrpos($file, '.');
  if ($start !== FALSE) {
    $lang_file = substr_replace($file, '.' . $language->language, $start, 0);
  }

  // file exists in version for given language
  if ($lang_file && file_exists($lang_file)) {
    $return = $lang_file;
  }
  // fallback
  elseif (file_exists($file)) {
    $return = $file;
  }

  return $return;
}

/**
 * Check if icon could be displayed on the given form
 *
 * @param string $form_id
 *
 * @returns boolean
 */
function _mojeid_promo_icon_display($form_id) {
  $forms = variable_get('mojeid_promo_icons', array());
  return !empty($forms[$form_id]);
}


//=============================================================================
//  MOJEID AX SCHEMA
//=============================================================================


/**
 * List of supported elements identifiers by the mojeID.cz provider.
 */
function mojeid_supported_elements() {
  return array(
    'http://axschema.org/namePerson',
    'http://axschema.org/namePerson/first',
    'http://axschema.org/namePerson/last',
    'http://axschema.org/namePerson/friendly',
    'http://axschema.org/company/name',
    'http://axschema.org/contact/postalAddress/home',
    'http://axschema.org/contact/postalAddressAdditional/home',
    'http://specs.nic.cz/attr/addr/main/street3',
    'http://axschema.org/contact/city/home',
    'http://axschema.org/contact/state/home',
    'http://axschema.org/contact/country/home',
    'http://axschema.org/contact/postalCode/home',
    'http://specs.nic.cz/attr/addr/bill/street',
    'http://specs.nic.cz/attr/addr/bill/street2',
    'http://specs.nic.cz/attr/addr/bill/street3',
    'http://specs.nic.cz/attr/addr/bill/city',
    'http://specs.nic.cz/attr/addr/bill/sp',
    'http://specs.nic.cz/attr/addr/bill/cc',
    'http://specs.nic.cz/attr/addr/bill/pc',
    'http://specs.nic.cz/attr/addr/ship/street',
    'http://specs.nic.cz/attr/addr/ship/street2',
    'http://specs.nic.cz/attr/addr/ship/street3',
    'http://specs.nic.cz/attr/addr/ship/city',
    'http://specs.nic.cz/attr/addr/ship/sp',
    'http://specs.nic.cz/attr/addr/ship/cc',
    'http://specs.nic.cz/attr/addr/ship/pc',
    'http://specs.nic.cz/attr/addr/mail/street',
    'http://specs.nic.cz/attr/addr/mail/street2',
    'http://specs.nic.cz/attr/addr/mail/street3',
    'http://specs.nic.cz/attr/addr/mail/city',
    'http://specs.nic.cz/attr/addr/mail/sp',
    'http://specs.nic.cz/attr/addr/mail/cc',
    'http://specs.nic.cz/attr/addr/mail/pc',
    'http://axschema.org/contact/phone/default',
    'http://axschema.org/contact/phone/home',
    'http://axschema.org/contact/phone/business',
    'http://axschema.org/contact/phone/cell',
    'http://axschema.org/contact/phone/fax',
    'http://axschema.org/contact/email',
    'http://specs.nic.cz/attr/email/notify',
    'http://specs.nic.cz/attr/email/next',
    'http://axschema.org/contact/web/default',
    'http://axschema.org/contact/web/blog',
    'http://specs.nic.cz/attr/url/personal',
    'http://specs.nic.cz/attr/url/work',
    'http://specs.nic.cz/attr/url/rss',
    'http://specs.nic.cz/attr/url/facebook',
    'http://specs.nic.cz/attr/url/twitter',
    'http://specs.nic.cz/attr/url/linkedin',
    'http://axschema.org/contact/IM/ICQ',
    'http://axschema.org/contact/IM/Jabber',
    'http://axschema.org/contact/IM/Skype',
    'http://specs.nic.cz/attr/im/google_talk',
    'http://specs.nic.cz/attr/im/windows_live',
    'http://specs.nic.cz/attr/contact/ident/vat_id',
    'http://specs.nic.cz/attr/contact/vat',
    'http://specs.nic.cz/attr/contact/ident/card',
    'http://specs.nic.cz/attr/contact/ident/pass',
    'http://specs.nic.cz/attr/contact/ident/ssn',
    'http://specs.nic.cz/attr/contact/student',
    'http://specs.nic.cz/attr/contact/valid',
    'http://specs.nic.cz/attr/contact/adult',
    'http://specs.nic.cz/attr/contact/image',
  );
}


/**
 * Returns mojeID schema elements
 *
 * @see mojeid_openid_ax_schema()
 */
function _mojeid_openid_client_ax_schema() {
   $attributes = array(

    // Home Address ===================================================

    'http://specs.nic.cz/attr/addr/main/street3' => array(
      //'identifier'  => 56,
      'identifier'  => 200,
      'label'       => t('Street 3'),
      'description' => t('Address or street 3'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Address'),
      'provider'    => 'mojeID',
    ),

    // Billing Address ================================================

    'http://specs.nic.cz/attr/addr/bill/street' => array(
      //'identifier'  => 57,
      'identifier'  => 201,
      'label'       => t('Street 1'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Billing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/bill/street2' => array(
      //'identifier'  => 58,
      'identifier'  => 202,
      'label'       => t('Street 2'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Billing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/bill/street3' => array(
      //'identifier'  => 59,
      'identifier'  => 203,
      'label'       => t('Street 3'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Billing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/bill/city' => array(
      'identifier'  => 204,
      'label'       => t('City'),
      'description' => t('Billing city name'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Billing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/bill/sp' => array(
      //'identifier'  => 61,
      'identifier'  => 205,
      'label'       => t('State/Province'),
      'description' => t('Billing state or province name'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Billing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/bill/cc' => array(
      //'identifier'  => 62,
      'identifier'  => 206,
      'label'       => t('Country'),
      'description' => t('Billing country code'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Billing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/bill/pc' => array(
      //'identifier'  => 63,
      'identifier'  => 207,
      'label'       => t('Postal code'),
      'description' => t('Billing postal code'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Billing-Address'),
      'provider'    => 'mojeID',
    ),

    // Shipping Address ================================================

    'http://specs.nic.cz/attr/addr/ship/street' => array(
      //'identifier'  => 64,
      'identifier'  => 208,
      'label'       => t('Street 1'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Shipping-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/ship/street2' => array(
      //'identifier'  => 65,
      'identifier'  => 209,
      'label'       => t('Street 2'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Shipping-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/ship/street3' => array(
      //'identifier'  => 66,
      'identifier'  => 210,
      'label'       => t('Street 3'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Shipping-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/ship/city' => array(
      //'identifier'  => 67,
      'identifier'  => 211,
      'label'       => t('City'),
      'description' => t('Shipping city name'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Shipping-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/ship/sp' => array(
      //'identifier'  => 68,
      'identifier'  => 212,
      'label'       => t('State/Province'),
      'description' => t('Shipping state or province name'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Shipping-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/ship/cc' => array(
      //'identifier'  => 69,
      'identifier'  => 212,
      'label'       => t('Country'),
      'description' => t('Shipping country code'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Shipping-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/ship/pc' => array(
      //'identifier'  => 70,
      'identifier'  => 213,
      'label'       => t('Postal code'),
      'description' => t('Shipping postal code'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Shipping-Address'),
      'provider'    => 'mojeID',
    ),

    // Mailing Address ================================================

    'http://specs.nic.cz/attr/addr/mail/street' => array(
      //'identifier'  => 71,
      'identifier'  => 214,
      'label'       => t('Street 1'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Mailing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/mail/street2' => array(
      //'identifier'  => 72,
      'identifier'  => 215,
      'label'       => t('Street 2'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Mailing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/mail/street3' => array(
      //'identifier'  => 73,
      'identifier'  => 216,
      'label'       => t('Street 3'),
      'description' => '',
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Mailing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/mail/city' => array(
      //'identifier'  => 74,
      'identifier'  => 217,
      'label'       => t('City'),
      'description' => t('Mailing city name'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Mailing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/mail/sp' => array(
      //'identifier'  => 75,
      'identifier'  => 218,
      'label'       => t('State/Province'),
      'description' => t('Mailing state or province name'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Mailing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/mail/cc' => array(
      //'identifier'  => 76,
      'identifier'  => 219,
      'label'       => t('Country'),
      'description' => t('Mailing country code'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Mailing-Address'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/addr/mail/pc' => array(
      //'identifier'  => 77,
      'identifier'  => 220,
      'label'       => t('Postal code'),
      'description' => t('Mailing postal code'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Mailing-Address'),
      'provider'    => 'mojeID',
    ),

    // Email ================================================

    'http://specs.nic.cz/attr/email/notify' => array(
      //'identifier'  => 78,
      'identifier'  => 221,
      'label'       => t('Notification email'),
      'description' => t('Internet SMTP email address as per RFC2822'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Email'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/email/next' => array(
      //'identifier'  => 79,
      'identifier'  => 222,
      'label'       => t('Other email'),
      'description' => t('Internet SMTP email address as per RFC2822'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Email'),
      'provider'    => 'mojeID',
    ),

    // Websites ================================================

    'http://specs.nic.cz/attr/url/personal' => array(
      //'identifier'  => 80,
      'identifier'  => 223,
      'label'       => t('Personal web page'),
      'description' => t('Personal web site URL'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#anyURI',
      'section'     => t('Web-Sites'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/url/work' => array(
      //'identifier'  => 81,
      'identifier'  => 224,
      'label'       => t('Work web page'),
      'description' => t('Work web site URL'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#anyURI',
      'section'     => t('Web-Sites'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/url/rss' => array(
      //'identifier'  => 82,
      'identifier'  => 225,
      'label'       => t('RSS URL'),
      'description' => t('RSS feed URL'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#anyURI',
      'section'     => t('Web-Sites'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/url/facebook' => array(
      //'identifier'  => 83,
      'identifier'  => 226,
      'label'       => t('Facebook URL'),
      'description' => t('Facebook URL'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#anyURI',
      'section'     => t('Web-Sites'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/url/twitter' => array(
      //'identifier'  => 84,
      'identifier'  => 227,
      'label'       => t('Twitter URL'),
      'description' => t('Twitter URL'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#anyURI',
      'section'     => t('Web-Sites'),
    ),
    'http://specs.nic.cz/attr/url/linkedin' => array(
      //'identifier'  => 85,
      'identifier'  => 228,
      'label'       => t('LinkedIn URL'),
      'description' => t('LinkedIn URL'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#anyURI',
      'section'     => t('Web-Sites'),
      'provider'    => 'mojeID',
    ),

    // Instant Messengers ================================================

    'http://specs.nic.cz/attr/im/google_talk' => array(
      //'identifier'  => 86,
      'identifier'  => 229,
      'label'       => t('Google Talk IM'),
      'description' => t('Google Talk instant messaging service handle'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Instant-Messaging'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/im/windows_live' => array(
      //'identifier'  => 87,
      'identifier'  => 230,
      'label'       => t('Windows Live IM'),
      'description' => t('Windows Live instant messaging service handle'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Instant-Messaging'),
      'provider'    => 'mojeID',
    ),

    // Identifiers ================================================

    'http://specs.nic.cz/attr/contact/ident/vat_id' => array(
      //'identifier'  => 88,
      'identifier'  => 231,
      'label'       => t('Company ID'),
      'description' => t('Company ID number'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Identifiers'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/contact/vat' => array(
      //'identifier'  => 89,
      'identifier'  => 232,
      'label'       => t('VAT'),
      'description' => t('VAT ID number'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Identifiers'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/contact/ident/card' => array(
      //'identifier'  => 90,
      'identifier'  => 233,
      'label'       => t('Personal card'),
      'description' => t('Personal ID number'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Identifiers'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/contact/ident/pass' => array(
      //'identifier'  => 91,
      'identifier'  => 234,
      'label'       => t('Passport'),
      'description' => t('Passport  ID number'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Identifiers'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/contact/ident/ssn' => array(
      //'identifier'  => 92,
      'identifier'  => 235,
      'label'       => t('Social security'),
      'description' => t('Social security number'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Identifiers'),
      'provider'    => 'mojeID',
    ),

    // Attributes ================================================

    'http://specs.nic.cz/attr/contact/student' => array(
      //'identifier'  => 93,
      'identifier'  => 236,
      'label'       => t('Student'),
      'description' => t('Student'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Attributes'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/contact/valid' => array(
      //'identifier'  => 94,
      'identifier'  => 237,
      'label'       => t('Valid'),
      'description' => t('Valid'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Attributes'),
      'provider'    => 'mojeID',
    ),
    'http://specs.nic.cz/attr/contact/adult' => array(
      //'identifier'  => 95,
      'identifier'  => 238,
      'label'       => t('Adult'),
      'description' => t('Adult'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#normalizedString',
      'section'     => t('Attributes'),
      'provider'    => 'mojeID',
    ),

    // Images ================================================

    'http://specs.nic.cz/attr/contact/image' => array(
      //'identifier'  => 96,
      'identifier'  => 239,
      'label'       => t('Image'),
      'description' => t('Binary image (base64 encoded)'),
      'type'        => 'http://www.w3.org/2001/XMLSchema#base64Binary',
      'section'     => t('Images'),
      'provider'    => 'mojeID',
    ),

  );

  return $attributes;
}
