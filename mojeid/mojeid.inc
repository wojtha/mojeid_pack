<?php

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
      'description' => t('Billing state or province name '),
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
      'description' => t('Shipping state or province name '),
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
      'description' => t('Mailing state or province name '),
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
