(function ($) {
/**
 * Update the summary for the module's vertical tab.
 */
Backdrop.behaviors.base_metaFieldsetSummaries = {
  attach: function (context) {
    $('fieldset#edit-base-meta', context).backdropSetSummary(function (context) {
      if ($('#edit-base-meta-enabled', context).is(':checked')) {
        return Backdrop.t('Tags defined');
      }
      else {
        return Backdrop.t('Use defaults');
      }
    });
  }
};

})(jQuery);

