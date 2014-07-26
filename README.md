cinder-mapped-memory
====================

Test to map memory between two cinder apps.  I envision this as a nice way to share data between 32bit and 64bit Cinder apps, in those situations where you can't go all 64bit.

I use boost that allows for a mapped memory region and also for inter process locking.

I tried to set it up so that the reader and writer did not need to be created in any specific order.

For reasons outside the scope of this document I chose not to use an interprocess mutex and just used the first bit of my mapped memory space for communication.