node-native-osx-filewatcher
===========================

Native node.js file watcher implementation for Mac OS X. Uses Mac OS X FSEvents API to monitor a directory instead of using fs.watchFile.

Based on https://github.com/alandipert/fswatch.

Why bother? Because node.js file watching is brtual on CPU usage as the number of files being watched grows. By using OS level events we can remove the burden of constantly checking each file being watched for changes.

End result? CPU usage drops to an insignificant factor when watching a large number of files. 

Support for other Operating Systems
---------------------------

This module could be extended to support Linux via inotify.
Same thing for Windows via FindFirstChangeNotification.
