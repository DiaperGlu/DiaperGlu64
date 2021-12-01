//
//  DiaperGluLifeOpenGLView.h
//  DiaperGluLifeApplication
//
//  Created by James Norris on 4/3/18.
//  Copyright (c) 2018 James Norris. All rights reserved.
//

@interface DiaperGluLifeOpenGLView : NSOpenGLView

- (void)doLifeOnce;

- (IBAction) doCursorUp: (id)sender;
- (IBAction) doCursorDown: (id)sender;
- (IBAction) doCursorLeft: (id)sender;
- (IBAction) doCursorRight: (id)sender;
- (IBAction) doToggleCursor: (id)sender;
- (IBAction) doDrawAtCursor: (id)sender;
- (IBAction) cursorDrawModeClear: (id)sender;
- (IBAction) cursorDrawModeSet: (id)sendoer;
- (IBAction) cursorDrawModeToggle: (id)sender;

- (IBAction) cursorDrawsADot: (id)sender;

- (IBAction) cursorDrawsABar3: (id)sender;
- (IBAction) cursorDrawsAToad: (id)sender;
- (IBAction) cursorDrawsABeacon: (id)sender;

- (IBAction) cursorDrawsAGlider5: (id)sender;
- (IBAction) cursorDrawsASmallSpaceship: (id)sender;

- (IBAction) cursorDrawsABlock4: (id)sender;
- (IBAction) cursorDrawsABeehive: (id)sender;
- (IBAction) cursorDrawsABread: (id)sender;
- (IBAction) cursorDrawsABoat: (id)sender;
- (IBAction) cursorDrawsATub: (id)sender;

- (IBAction) cursorDrawsALadder: (id)sender;

- (IBAction) cursorDrawsAnAcorn: (id)sender;
- (IBAction) cursorDrawsARPentomino: (id)sender;

@property uint64 cursorstate;

@end
