#!/usr/bin/env bpftrace
kprobe:generic_file_write_iter,
kprobe:generic_file_read_iter
{
    @[comm] = count();
}
interval:s:15
{
    time();
    print(@);
    clear(@);
}
