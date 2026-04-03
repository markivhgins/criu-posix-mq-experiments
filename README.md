# CRIU POSIX Message Queue Experiment

## Goal
Test CRIU behavior when checkpointing a process using POSIX message queues.

## Setup
- Ubuntu 24.04
- CRIU built from source

## Test Program
A simple C program using mq_open and mq_send.

## Observation
CRIU fails to checkpoint the process when POSIX message queues are involved.

## Logs
See dump.log

## Insight
CRIU currently cannot checkpoint processes using POSIX message queues due to:
Inability to handle mqueue file descriptors
Lack of a mechanism to inspect queue contents without modifying them
