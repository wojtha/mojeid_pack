
/* Taken from Drupal.behaviors.openid */
Drupal.behaviors.mojeid = function(context) {
  var $loginElements = $('#edit-name-wrapper, #edit-pass-wrapper, li.openid-link, li.mojeid-link');
  var $mojeIdElements = $('#edit-mojeid-identifier-wrapper, li.mojeid-user-link');

  // This behavior attaches by ID, so is only valid once on a page.
  if (!$('#edit-mojeopenid-identifier.mojeid-processed').size() && $('#edit-mojeid-identifier').val()) {
    $('#edit-mojeid-identifier').addClass('mojeid-processed');
    $loginElements.hide();
    // Use .css('display', 'block') instead of .show() to be Konqueror friendly.
    $mojeIdElements.css('display', 'block');
  }
  $('li.mojeid-link:not(.mojeid-processed)', context)
    .addClass('mojeid-processed')
    .click( function() {
      $loginElements.hide();
      $mojeIdElements.css('display', 'block');
      // Remove possible error message.
      $('#edit-name, #edit-pass').removeClass('error');
      $('div.messages.error').hide();
      // Set focus on OpenID Identifier field.
      $('#edit-mojeid-identifier')[0].focus();
      return false;
    });
  $('li.mojeid-user-link:not(.mojeid-processed)', context)
    .addClass('mojeid-processed')
    .click(function() {
      $mojeIdElements.hide();
      $loginElements.css('display', 'block');
      // Clear OpenID Identifier field and remove possible error message.
      $('#edit-mojeid-identifier').val('').removeClass('error');
      $('div.messages.error').css('display', 'block');
      // Set focus on username field.
      $('#edit-name')[0].focus();
      return false;
    });
  $('li.openid-link:not(.mojeid-processed)', context)
    .addClass('mojeid-processed')
    .click( function() {
      $('li.mojeid-link').hide();
      return false;
    });
  $('li.user-link:not(.mojeid-processed)', context)
    .addClass('mojeid-processed')
    .click(function() {
      $('li.mojeid-link').css('display', 'block');
      return false;
    });

  // Works only when page is loaded, because older browsers (IE < 8, FF < 3.6)
  // don't support hashchange event. If we want to support x-browser compatible
  // hash change monitoring, there is a jQ plugin for this:
  // http://plugins.jquery.com/project/hashchange
  // if (window.location.pathname == '/user' && window.location.hash == '#mojeid') {
  if (window.location.href.search('/user#mojeid') >= 0) {
    $loginElements.hide();
    // Use .css('display', 'block') instead of .show() to be Konqueror friendly.
    $mojeIdElements.css('display', 'block');
  }

};

