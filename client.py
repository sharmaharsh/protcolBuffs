import json
import requests
import sys

server = "http://localhost:8081/"

if __name__ == "__main__":
  try:
    file_contents = file(sys.argv[1], 'rb').read()
  except:
    print("USAGE: client <filename>")

  r = requests.post(server, \
        data = {"def": file_contents})

  if r.status_code != 200:
    print "ERROR:", r.text
  else:
    print r.text
