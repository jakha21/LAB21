from nornir import InitNornir
from nornir_netmiko import netmiko_send_command
from nornir_netmiko import netmiko_send_config
from nornir_utils.plugins.functions import print_result

def run():
    nr = InitNornir(config_file="config.yaml")
    nr.run(task=netmiko_send_config, config_commands=["management api http-commands","no shutdown"])
    result = nr.run(task=netmiko_send_command, command_string="show management api http-commands")
    print_result(result)
    
if __name__ == "__main__":
    run()