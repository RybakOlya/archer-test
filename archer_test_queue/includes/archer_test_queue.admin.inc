<?php

/**
 * @file
 * Contains configuration form and queue function.
 */

/**
 * Configuration form.
 */
function archer_test_queue_remove_old_nodes_admin_config_form($form, &$form_state) {
  $form['description'] = [
    '#markup' => t('You are here because you want to delete nodes, older than 10 days from the system.<br> To do that just click on "Delete nodes" button below'),
  ];

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Delete nodes'),
  ];

  return $form;
}

/**
 * Submission function. Prepare queue and run cron to execute it.
 */
function archer_test_queue_remove_old_nodes_admin_config_form_submit($form, &$form_state) {
  // Choosing nodes older than 10 days.
  $nids = db_select('node', 'n')
    ->fields('n', ['nid'])
    ->condition('n.created', strtotime('-1 day'), '<')
    ->orderBy('n.created', 'ASC')
    ->execute()->fetchCol();

  // Add founded nodes to the Queue.
  if (!empty($nids)) {
    $queue = DrupalQueue::get('archer_test_queue_delete_old_nodes');
    $queue->createQueue();
    foreach ($nids as $nid) {
      $queue->createItem($nid);
    }
  $count = $queue->numberOfItems();

  drupal_cron_run();
  drupal_set_message(t('@count nodes were successfully deleted', ['@count' => $count]));
  }
  else {
    drupal_set_message(t('You have no nodes older than 10 days in the system'), 'error');
  }
}
