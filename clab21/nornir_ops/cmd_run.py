#!/usr/bin/env python3

import os
import sys
import click
from nornir import InitNornir
from nornir_utils.plugins.functions import print_result
import importlib
#from tasks.detour import detour
from nornir.core.filter import F

@click.command()
@click.option('--task', required=True, help='Task to run, e.g. send_config')
@click.option("--hosts", help="Comma-separated list of hosts to run the task on.")
@click.option("--intf", help="Interface to target (for tasks like detour).")

def main(task, hosts, intf):
    nr = InitNornir(config_file="config.yaml")

    if hosts:
        host_list = [h.strip() for h in hosts.split(",")]
        nr = nr.filter(F(name__in=host_list))

    try:
        task_module = importlib.import_module(f"tasks.{task}")
        result = nr.run(task=task_module.detour, intf=intf)
        print_result(result)
    except ModuleNotFoundError:
            click.echo(f"❌ Task '{task_name}' not found in tasks/", err=True)
            sys.exit(1)

if __name__ == "__main__":
    main()
