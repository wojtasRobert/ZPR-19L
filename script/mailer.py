import argparse
import configparser
import smtplib, ssl

TITLE = "Resmond -- limit violated ({command})"

MESSAGE = """
Hi,

The process `{command}` with pid `{pid}` just violated its {resource} limit: {limit}%.

Cheers
Resmond
"""

CONFIG_FILE = 'mailer.ini'

if __name__ == '__main__':
    # Context
    parser = argparse.ArgumentParser()
    parser.add_argument('pid')
    parser.add_argument('command')
    parser.add_argument('resource')
    parser.add_argument('limit')
    args = parser.parse_args()
    msg_context = vars(args)

    # Config
    config = configparser.ConfigParser()
    try:
        with open(CONFIG_FILE, 'x') as configfile:
            config['DEFAULT']['server'] = ''
            config['DEFAULT']['port'] = ''
            config['DEFAULT']['password'] = ''
            config['DEFAULT']['from'] = ''
            config['DEFAULT']['to'] = ''
            config.write(configfile)
    except FileExistsError:
        config.read(CONFIG_FILE)

    context = ssl.create_default_context()
    with smtplib.SMTP(config['DEFAULT']['server'], config['DEFAULT']['port']) as server:
        server.ehlo()  # Can be omitted
        server.starttls(context=context)
        server.ehlo()  # Can be omitted
        server.login(config['DEFAULT']['from'], config['DEFAULT']['password'])
        server.sendmail(config['DEFAULT']['from'], config['DEFAULT']['to'], MESSAGE.format(**msg_context))
