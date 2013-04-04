// Micro-GLUT, bare essentials
// Single-file GLUT subset.
// By Ingemar Ragnemalm 2012

// I wrote this since GLUT seems not to have been updated to support
// creation of a 3.2 context on the Mac. With a single-file solution like
// this, there is no installation problems at all and it is also easy
// to hack around in a local copy as needed.

// To do: Linux/Windows/iOS ports. (Preliminary versions exist of both.)
// Some additional features. Text rendering? Menus? Multi-window?

// Changes:
// Several additions for the lab 3 version: Simple menu, glutTimerFunc and my own glutrepeatingTimerFunc.
// glutKeyboardUpFunc, glutInitDisplayMode.
// 120209: Some more additions, like glutMotionFunc and GLUT_RIGHT_BUTTON.
// 120228: Added glutSetWindowTitle, glutKeyIsDown, glutInitContextVersion
// NOTE: glutInitContextVersion is now required for 3.2 code!
// NOTE: This statement is incorrect; MicroGLUT still only supports 3.2 and with no extra calls.
// 120301: Resizable window. Correct vertical window position.
// 120808: Fixed a bug that caused error messages. (Calling finishLaunching twice.)
// 120822: Stencil now uses 8 instead of 32
// 120905: Two corrections suggested by Marcus Stenbäck.
// 120913: Added 2-button emulation with CTRL
// 130103: Added [m_context makeCurrentContext]; in all user callbacks. (GL calls had no effect.)


#import <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <sys/time.h>

#include "MicroGlut.h"

// Vital internal variables

void (*gDisplay)(void);
void (*gReshape)(int width, int height);
void (*gKey)(unsigned char key, int x, int y);
void (*gKeyUp)(unsigned char key, int x, int y);
void (*gMouseMoved)(int x, int y);
void (*gMouseDragged)(int x, int y);
void (*gMouseFunc)(int button, int state, int x, int y);
unsigned int gContextInitMode = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
void (*gIdle)(void);
char updatePending = 1;
char gRunning = 1;
char gKeymap[256];
int gContextVersionMajor = 0;
int gContextVersionMinor = 0;

// -----------

// Globals (was in GLViewDataPtr)
NSOpenGLContext	*m_context;
float lastWidth, lastHeight;
NSView *theView;

void MakeContext(NSView *view)
{
	NSOpenGLPixelFormat *fmt;
	int zdepth, sdepth;
	int profile = 0, profileVersion = 0;
	
	if (gContextInitMode & GLUT_DEPTH)
		zdepth = 32;
	else
		zdepth = 0;
	
	if (gContextInitMode & GLUT_STENCIL)
		sdepth = 8;
	else
		sdepth = 0;
	
	if (gContextVersionMajor == 3)
	// I ignore the minor version for now, 3.2 is all we can choose currently
	{
		profile = NSOpenGLPFAOpenGLProfile;
		profileVersion = NSOpenGLProfileVersion3_2Core;
	}
	// UNUSED - will be fixed when GL2 is supported
	
	NSOpenGLPixelFormatAttribute attrs[] =
	{
		NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, zdepth,
		NSOpenGLPFAStencilSize, sdepth,
		profile, profileVersion,
		0
	};

	// Save view (should be packaged with context for multi-window application - to do)
	theView = view;
	
	// Init GL context
	fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes: &attrs[0]];
	
	m_context = [[NSOpenGLContext alloc] initWithFormat: fmt shareContext: nil];
	[fmt release];
	[m_context makeCurrentContext];
}



// -------------------- View ------------------------

@interface TestView : NSView <NSWindowDelegate> { }
-(void)drawRect:(NSRect)rect;
-(void)keyDown:(NSEvent *)theEvent;
-(void)keyUp:(NSEvent *)theEvent;
-(void)mouseMoved:(NSEvent *)theEvent;
-(void)mouseDragged:(NSEvent *)theEvent;
-(void)mouseDown:(NSEvent *)theEvent;
-(void)mouseUp:(NSEvent *)theEvent;
-(void)rightMouseDown:(NSEvent *)theEvent;
-(void)rightMouseUp:(NSEvent *)theEvent;
-(void)windowDidresize:(NSNotification *)note;
@end

#define Pi 3.1415

@implementation TestView

-(void) mouseMoved:(NSEvent *)theEvent
{
	NSPoint p;
	[m_context makeCurrentContext];
	
	if (gMouseMoved != nil)
	{
		p = [theEvent locationInWindow];
		p = [self convertPoint: p fromView: nil];
		gMouseMoved(p.x, p.y);
	}
}

-(void) mouseDragged:(NSEvent *)theEvent
{
	NSPoint p;
	[m_context makeCurrentContext];
	
	if (gMouseDragged != nil)
	{
		p = [theEvent locationInWindow];
		p = [self convertPoint: p fromView: nil];
		gMouseDragged((int)p.x, (int)p.y);
	}
}

// Clone of above, but necessary for supporting the alternative button. Thanks to Marcus Stenbäck!
-(void) rightMouseDragged:(NSEvent *)theEvent
{
	NSPoint p;
	[m_context makeCurrentContext];
	
	if (gMouseDragged != nil)
	{
		p = [theEvent locationInWindow];
		p = [self convertPoint: p fromView: nil];
		gMouseDragged((int)p.x, (int)p.y);
	}
}

// Remember if last press on the left (default) button was modified to
// a "right" with CTRL
char gLeftIsRight = 0;

-(void) mouseDown:(NSEvent *)theEvent
{
	NSPoint p;
	[m_context makeCurrentContext];
	
	if (gMouseFunc != nil)
	{
		// Convert location in window to location in view
		p = [theEvent locationInWindow];
		p = [self convertPoint: p fromView: nil];
		
		if ([NSEvent modifierFlags] & NSControlKeyMask)
		{
			gMouseFunc(GLUT_RIGHT_BUTTON, GLUT_DOWN, p.x, p.y);
			gLeftIsRight = 1;
		}
		else
		{
			gMouseFunc(GLUT_LEFT_BUTTON, GLUT_DOWN, p.x, p.y);
			gLeftIsRight = 0;
		}
	}
}

-(void) mouseUp:(NSEvent *)theEvent
{
	NSPoint p;
	[m_context makeCurrentContext];
	
	if (gMouseFunc != nil)
	{
		// Convert location in window to location in view
		p = [theEvent locationInWindow];
		p = [self convertPoint: p fromView: nil];
		
		// Assuming that the user won't release CTRL - then it looks like different buttons
		if (gLeftIsRight)
			gMouseFunc(GLUT_RIGHT_BUTTON, GLUT_UP, p.x, p.y);
		else
			gMouseFunc(GLUT_LEFT_BUTTON, GLUT_UP, p.x, p.y);
	}
}

-(void) rightMouseDown:(NSEvent *)theEvent
{
	NSPoint p;
	[m_context makeCurrentContext];
	
	if (gMouseFunc != nil)
	{
		// Convert location in window to location in view
		p = [theEvent locationInWindow];
		p = [self convertPoint: p fromView: nil];
		gMouseFunc(GLUT_RIGHT_BUTTON, GLUT_DOWN, p.x, p.y);
	}
}

-(void) rightMouseUp:(NSEvent *)theEvent
{
	NSPoint p;
	[m_context makeCurrentContext];
	
	if (gMouseFunc != nil)
	{
		// Convert location in window to location in view
		p = [theEvent locationInWindow];
		p = [self convertPoint: p fromView: nil];
		gMouseFunc(GLUT_RIGHT_BUTTON, GLUT_UP, p.x, p.y);
	}
}

-(void)keyDown:(NSEvent *)theEvent
{
	char *chars;
	[m_context makeCurrentContext];
	
	chars = (char *)[[theEvent characters] cStringUsingEncoding: NSASCIIStringEncoding];
	if (chars != NULL)
	{
		if (gKey != NULL) // Change 120913
			gKey(chars[0], 0, 0); // TO DO: x and y
//			printf("keydown %c\n", chars[0]);
		
		gKeymap[(unsigned int)chars[0]] = 1;
	}
}

-(void)keyUp:(NSEvent *)theEvent
{
	char *chars;
	
	chars = (char *)[[theEvent characters] cStringUsingEncoding: NSASCIIStringEncoding];
	if (chars != NULL)
	{
		if (gKeyUp != NULL) // Change 120913
			gKeyUp(chars[0], 0, 0); // TO DO: x and y
//			printf("keyup %c\n", chars[0]);

		gKeymap[(unsigned int)chars[0]] = 0;
	}
}

- (BOOL)acceptsFirstResponder	{ return YES; }

- (BOOL)becomeFirstResponder	{ return YES; }

- (BOOL)resignFirstResponder	{ return YES; }

-(void)drawRect:(NSRect)rect
{
	if (([theView frame].size.width != lastWidth) || ([theView frame].size.height != lastHeight))
	{
		lastWidth = [theView frame].size.width;
		lastHeight = [theView frame].size.height;
		
		// Only needed on resize:
		[m_context clearDrawable];
//		glViewport(0, 0, [theView frame].size.width, [theView frame].size.height);
		
		if (gReshape != NULL)
			gReshape([theView frame].size.width, [theView frame].size.height);
	}
	
	[m_context setView: theView];
	[m_context makeCurrentContext];
	
	// Draw
	if (gDisplay != NULL)
		gDisplay();
	updatePending = 0;
	
	[m_context flushBuffer];
	[NSOpenGLContext clearCurrentContext];
}

-(void)windowWillClose:(NSNotification *)note
{
	[[NSApplication sharedApplication] terminate:self];
}

-(void)windowDidresize:(NSNotification *)note
{
	// Call gReshape now or in drawRect?
}

@end


// -------------------- Timer ------------------------

// Data for timer
@interface TimerInfoRec : NSObject
{
@public	void (*func)(int arg);
	int arg;
@private
}
@end

@implementation TimerInfoRec
@end

// Mini-mini class for the timer
@interface TimerController : NSObject { }
-(void)timerFireMethod:(NSTimer *)t;
@end

NSTimer	*gTimer;
TimerController	*myTimerController;
NSView	*view;

// Timer!
@implementation TimerController
-(void)timerFireMethod:(NSTimer *)t;
{
	TimerInfoRec *tr;
	
	if (t.userInfo != nil) // One-shot timer with a TimerInfoRec
	{
		tr = t.userInfo;
		tr->func(tr->arg);
		[tr release];
//		((TimerInfoRec *)(t.userInfo))->func(((TimerInfoRec *)(t.userInfo))->arg);
//		free((TimerInfoRec *)(t.userInfo));
	}
	else
	{
		[view setNeedsDisplay: YES];
		updatePending = 1;
	}
}
@end


void glutPostRedisplay()
{
	[theView setNeedsDisplay: YES];
	updatePending = 1;
}


// home()

#include <Carbon/Carbon.h>
#include <stdio.h>

void home()
{
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
	char path[PATH_MAX];
	if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
	{
		// error!
		return;
	}
	CFRelease(resourcesURL);

	chdir(path);
	printf("Current Path: %s\n", path);
}

// ------------------ Main program ---------------------

@interface MGApplication : NSApplication
@end

@implementation MGApplication
/* Invoked from the Quit menu item */
- (void)terminate:(id)sender
{
	gRunning = 0;
}
@end

MGApplication *myApp;
NSView *view;
NSAutoreleasePool *pool;
NSWindow *window;
static struct timeval timeStart;

void CreateMenu()
{
	NSMenu *mainMenu, *theMiniMenu;
	NSMenuItem *menuItem2, *dummyItem;

	// Create main menu = menu bar
	mainMenu = NSMenu.alloc;
	[mainMenu initWithTitle: @""];
	[NSApp setMainMenu: mainMenu];

	// Create the custom menu
	theMiniMenu = NSMenu.alloc;
	[theMiniMenu initWithTitle: @"The MiniMenu"];
	
	// Create a menu item with standard message
	menuItem2 = NSMenuItem.alloc;
	[menuItem2 initWithTitle: @"Hide" action: @selector(hide:) keyEquivalent: @"h"];
	[menuItem2 setKeyEquivalentModifierMask: NSCommandKeyMask];
	[theMiniMenu addItem: menuItem2];
	
	// Create a menu item with standard message
	menuItem2 = NSMenuItem.alloc;
	[menuItem2 initWithTitle: @"Hide others" action: @selector(hideOtherApplications:) keyEquivalent: @"h"];
	[menuItem2 setKeyEquivalentModifierMask: NSCommandKeyMask | NSAlternateKeyMask];
	[theMiniMenu addItem: menuItem2];
	
	// Create a menu item with standard message
	menuItem2 = NSMenuItem.alloc;
	[menuItem2 initWithTitle: @"Show all" action: @selector(unhideAllApplications:) keyEquivalent: @"h"];
	[menuItem2 setKeyEquivalentModifierMask: NSCommandKeyMask | NSControlKeyMask];
	[theMiniMenu addItem: menuItem2];
	
	// Create a menu item with standard message
	menuItem2 = NSMenuItem.alloc;
	[menuItem2 initWithTitle: @"Quit" action: @selector(terminate:) keyEquivalent: @"q"];
	[menuItem2 setKeyEquivalentModifierMask: NSCommandKeyMask];
	[theMiniMenu addItem: menuItem2];
	
	// Adding a menu is done with a dummy item to connect the menu to its parent
	dummyItem = NSMenuItem.alloc;
	[dummyItem initWithTitle: @"" action: nil keyEquivalent: @""];
	[dummyItem setSubmenu: theMiniMenu];

	[mainMenu addItem: dummyItem];
}

void glutInit(int *argcp, char **argv)
{
	pool = [NSAutoreleasePool new];
	myApp = [MGApplication sharedApplication];
	
	[NSApp setActivationPolicy: NSApplicationActivationPolicyRegular]; // Thanks to Marcus Stenbäck
	
	gRunning = 1;
	home();
	gettimeofday(&timeStart, NULL);
	CreateMenu();
	myTimerController = [TimerController alloc];

	int i;
	for (i = 0; i < 256; i++) gKeymap[i] = 0;
}

int gWindowPosX = 10;
int gWindowPosY = 50;
int gWindowWidth = 400;
int gWindowHeight = 400;

void glutInitWindowPosition (int x, int y)
{
	gWindowPosX = x;
	gWindowPosY = y;
}
void glutInitWindowSize (int width, int height)
{
	gWindowWidth = width;
	gWindowHeight = height;
}
void glutCreateWindow (char *windowTitle)
{
// To do: Should get screen height instead of 1000
	NSRect frame = NSMakeRect(gWindowPosX, NSScreen.mainScreen.frame.size.height - gWindowPosY-gWindowHeight, gWindowWidth, gWindowHeight);
	
	window = [NSWindow alloc];
	[window initWithContentRect:frame
					styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
					backing:NSBackingStoreBuffered
					defer:false];
	
	[window setTitle: [[NSString alloc] initWithCString:windowTitle
				encoding:NSMacOSRomanStringEncoding]];

	view = [TestView alloc];
	[view initWithFrame: frame];
	[window setAcceptsMouseMovedEvents:YES];

	// OpenGL init!
	MakeContext(view);

// Moved from main loop
//	[window setContentView: view];
	[window setDelegate: (TestView*)view];
	[window makeKeyAndOrderFront: nil];
}

void glutMainLoop()
{
	[window setContentView: view];
//	[window setDelegate: (TestView*)view];
//	[window makeKeyAndOrderFront: nil];
	// Main loop
//	[myApp run];

	[myApp finishLaunching];

	NSEvent *event;

	while (gRunning)
	{
		[pool release];
		pool = [NSAutoreleasePool new];
		
		event = [myApp nextEventMatchingMask: NSAnyEventMask
//							untilDate: [NSDate dateWithTimeIntervalSinceNow: 0.0]
							untilDate: [NSDate distantFuture]
							inMode: NSDefaultRunLoopMode
							dequeue: true
							];
		
		[myApp sendEvent: event];
		[myApp updateWindows];
	
		if (gIdle != NULL)
			if (!updatePending)
				gIdle();
	}
}

// This won't work yet
void glutCheckLoop()
{
	[myApp runOnce];
	
	if (gIdle != NULL)
		if (!updatePending)
			gIdle();
	
	[pool release];
	pool = [NSAutoreleasePool new];
}

void glutTimerFunc(int millis, void (*func)(int arg), int arg)
{
	TimerInfoRec *timerInfo = [TimerInfoRec alloc];
	timerInfo->arg = arg;
	timerInfo->func = func;

	gTimer = [NSTimer
		scheduledTimerWithTimeInterval: millis/1000.0
		target: myTimerController
		selector: @selector(timerFireMethod:)
		userInfo: timerInfo
		repeats: NO];
}

// Added by Ingemar
void glutRepeatingTimer(int millis)
{
	gTimer = [NSTimer
		scheduledTimerWithTimeInterval: millis/1000.0
		target: myTimerController
		selector: @selector(timerFireMethod:)
		userInfo: nil
		repeats: YES];
}

// Bad name, will be removed
void glutRepeatingTimerFunc(int millis)
{
	glutRepeatingTimer(millis);
}

void glutDisplayFunc(void (*func)(void))
{
	gDisplay = func;
}

void glutReshapeFunc(void (*func)(int width, int height))
{
	gReshape = func;
}

void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y))
{
	gKey = func;
}

void glutKeyboardUpFunc(void (*func)(unsigned char key, int x, int y))
{
	gKeyUp = func;
}

void glutPassiveMotionFunc(void (*func)(int x, int y))
{
	gMouseMoved = func;
}

void glutMotionFunc(void (*func)(int x, int y))
{
	gMouseDragged = func;
}

void glutMouseFunc(void (*func)(int button, int state, int x, int y))
{
	gMouseFunc = func;
}

// You can safely skip this
void glutSwapBuffers()
{
 	[m_context flushBuffer];
}

int glutGet(int type)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_usec - timeStart.tv_usec) / 1000 + (tv.tv_sec - timeStart.tv_sec)*1000;
}

void glutInitDisplayMode(unsigned int mode)
{
	gContextInitMode = mode;
}

void glutIdleFunc(void (*func)(void))
{
// glutIdleFunc not recommended.
	gIdle = func;
	glutRepeatingTimerFunc(10);
}

void glutReshapeWindow(int width, int height)
{
	NSRect r;
	
	r = [window frame];
	r.size.width = width;
	r.size.height = height;
	[window setFrame: r display: true];
}

void glutSetWindowTitle(char *title)
{
	[window setTitle: [NSString stringWithUTF8String: title]];
}

char glutKeyIsDown(unsigned char c)
{
	return gKeymap[(unsigned int)c];
}

void glutInitContextVersion(int major, int minor)
{
	gContextVersionMajor = major;
	gContextVersionMinor = minor;
}

// glutInitContextFlags(int flags); Add this?

