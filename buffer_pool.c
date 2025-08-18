function fetch_page(page_id) : // 1. Check if page is already in the pool
                               if page_table.contains(page_id) : frame_index = page_table.get(page_id)
                                                                                   frame = pool[frame_index] lru_manager.move_to_head(frame) // Mark as recently used
                                                                                           frame.pin_count++ return frame

                                                                                           // 2. Page is not in pool (Cache Miss)
                                                                                           // Find a frame to place the new page in
                                                                                           victim_frame_index = lru_manager.get_victim() // Find victim from tail of list
                                                                                                                victim_frame = pool[victim_frame_index]

                                                                                                                               // 3. If victim is in use, fail or wait. For simplicity, assume we find one.
                                                                                                                               if victim_frame.pin_count
                                                                                                                               > 0 :
    // Handle error: no frames available to evict

    // 4. Write victim back to disk if it's dirty
    if victim_frame.is_dirty : disk_manager.write_page(victim_frame.page_id, victim_frame.data)

                               // 5. Update the page table to remove the old page mapping
                               page_table.remove(victim_frame.page_id)

                               // 6. Read new page from disk into the victim's frame
                               new_data = disk_manager.read_page(page_id)
                                                                                                                                   victim_frame.data = new_data victim_frame.page_id = page_id victim_frame.is_dirty = false victim_frame.pin_count = 1

                                                                                                                                                                                                                                                      // 7. Update data structures for the new page
                                                                                                                                                                                                                                                      page_table.put(page_id, victim_frame_index)
                                                                                                                                                                                                                                                          lru_manager.move_to_head(victim_frame)

                                                                                                                                                                                                                                                              return victim_frame