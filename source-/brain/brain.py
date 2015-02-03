__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '10/01/15'

import logging
import sys
import asyncore
import udp_client


def init_logger():
    log = logging.getLogger('brain')
    log.setLevel(logging.INFO)
    format = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
    ch = logging.StreamHandler(sys.stdout)
    ch.setFormatter(format)
    log.addHandler(ch)
    return log


if __name__ == "__main__":
    logger = init_logger()
    logger.info('Brain started')
    udp_client.Start(logger)
    asyncore.loop()