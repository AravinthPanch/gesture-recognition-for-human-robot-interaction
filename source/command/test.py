__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__date__ = '10/07/15'

import json

message = "{\"INFO\":\"Both hands are losa\"}"
msg = json.loads(message)



if "INFO" in msg:
    if "lost" in msg['INFO']:
        print "true"
