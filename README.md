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
POSIX message queues cannot be inspected without consuming messages (mq_receive),
which makes checkpointing unsafe without kernel support.
