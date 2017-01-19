<?php

/**
 * @file
 * Contains configuration form for batch.
 */

/**
 * Configuration form.
 */
function archer_test_batch_update_dates_admin_config_form($form, &$form_state) {
  $form['archer_test_batch_date_format'] = [
    '#type' => 'textfield',
    '#title' => t('Enter date relatively to current'),
    '#description' => t('Enter date in format: @format or "+1 day" or "-30 minutes". Use "now" or "today" to set current date', [
      '@format' => date('Y-m-d H:i:s'),
    ]),
    '#required' => TRUE,
  ];

  $form['archer_test_batch_size'] = [
    '#type' => 'select',
    '#title' => t('Batch size'),
    '#options' => [
      '50' => 50,
      '100' => 100,
      '200' => 200,
      '500' => 500,
      '1000' => 1000,
    ],
    '#required' => TRUE,
    '#multiple' => FALSE,
  ];

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Start batch'),
  ];

  return $form;
}

/**
 * Configuration form validate function.
 */
function archer_test_batch_update_dates_admin_config_form_validate($form, &$form_state) {
  // Check if date entered in a valid format.
  if (!strtotime($form_state['values']['archer_test_batch_date_format'])) {
    form_error($form['archer_test_batch_date_format'], t('Date format is invalid.'));
  }
}

/**
 * Configuration form submit function.
 */
function archer_test_batch_update_dates_admin_config_form_submit($form, &$form_state) {
  $new_date = strtotime($form_state['values']['archer_test_batch_date_format']);
   batch_set(archer_test_batch_batch($new_date, $form_state['values']['archer_test_batch_size']));
}
