;;;;
;;;;	REGPATH.SH
;;;;
;;;;	(c) Sierra On-Line, Inc, 1992
;;;;
;;;;	Author: 	J. Mark Hood
;;;;	Updated:
;;;;
;;;;	This header file is used by REGPATH.SC


(define NEXTROOM		$7FFF	)		; Marks end of path for a given room.
											; Next value in array is room number.

(define RP_QUIT			0)			; Cue s caller when finished.
(define RP_STARTOVER		$0001)	; Starts region path over when finished.

(define RP_REVERSE		$0002)	; Implemented by: Randy MacNeill
