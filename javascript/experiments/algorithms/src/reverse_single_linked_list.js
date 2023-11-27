/** @typedef {{ value: number, next?: Node }} Node */

// Wrap recursive function to scope variables outside of recursion calls to
// avoid using old values in subsequent calls.
function reverse_single_linked_list() {
  // Store values the recursion needs outside the function to avoid additional
  // memory usage.
  /** @type {Node | null} */
  let head_of_reverse_linked_list = null;
  /** @type {Node | null} */
  let current_node = null;
  /** @type {Node | null} */
  let previous_node = null;

  /**
   * @param {Node | undefined} node
   * @returns {Node}
   */
  return function reverse(node) {
    if (node) {
      reverse(node.next);
      // Recycle the current node to avoid unnecessary memory consumption.
      current_node = node;
      // Break the cyclic dependency. We can safely ignore the next value
      // because we are traversing the list in reverse.
      delete current_node.next;

      if (head_of_reverse_linked_list) {
        // Create subsequent nodes.
        previous_node.next = current_node;
        previous_node = previous_node.next;
      } else {
        // Initialize.
        head_of_reverse_linked_list = current_node;
        previous_node = head_of_reverse_linked_list;
      }
    }

    return head_of_reverse_linked_list;
  };
}

module.exports.reverse_single_linked_list = reverse_single_linked_list;
