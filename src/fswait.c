#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <CoreServices/CoreServices.h>

static void (*nodeCallback)(int, char **) = NULL;

static void callback(
    ConstFSEventStreamRef streamRef,
    void *clientCallBackInfo,
    size_t numEvents,
    void *eventPaths,
    const FSEventStreamEventFlags eventFlags[],
    const FSEventStreamEventId eventIds[])
{
   nodeCallback(numEvents, (char **)eventPaths);
}

void watchFiles(const char *path, void (*cb)(int, char **)) {
  nodeCallback = cb;
  CFStringRef mypath = CFStringCreateWithCString(NULL, path, kCFStringEncodingUTF8);
  CFArrayRef pathsToWatch = CFStringCreateArrayBySeparatingStrings (NULL, mypath, CFSTR(":"));

  void *callbackInfo = NULL;
  FSEventStreamRef stream;
  CFAbsoluteTime latency = 1.0;

  stream = FSEventStreamCreate(NULL,
    &callback,
    callbackInfo,
    pathsToWatch,
    kFSEventStreamEventIdSinceNow,
    latency,
    kFSEventStreamCreateFlagFileEvents
  );

  FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
  FSEventStreamStart(stream);
  CFRunLoopRun();
}
