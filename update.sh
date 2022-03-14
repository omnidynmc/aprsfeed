#!/bin/bash
svn update && make makeall && killall -INT aprsfeed && sleep 30 && ./aprsfeed.botchk && cd logs && tail -f aprsfeed.log
