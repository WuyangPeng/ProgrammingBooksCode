/* -*- C++ -*- */
// CC_LockSet.h,v 1.15 2001/02/02 02:31:46 fhunleth Exp

// ============================================================================
//
// = LIBRARY
//    TAO/orbsvcs/Concurrency_Service
//
// = FILENAME
//      CC_LockSet.h
//
// = DESCRIPTION
//      This class implements the lock set interface from the
//      concurrency service.
//
//      In the present implementation the multiple possesion semantics
//      is implemented for non-transactional clients. In future
//      versions this should be changed because the multiple possesion
//      semantics does not apply to non-transactional clients. This
//      can be accomplished in the following manner:
//      - Make a class with the same functiallity as the CC_LockSet
//        class as a base class for both implementations.
//      - The functionallity that should be separated out in the
//        subclasses is the compatible function which should always
//        return false because no locks can be held simultanously with
//        non-transactional clients.
//      - Use these classes from the classes that inherits the
//        servant properties, i.e. the way CC_LockSet does now.
//
// = AUTHORS
//      Torben Worm <tworm@cs.wustl.edu>
//
// ============================================================================

#ifndef _CC_LOCKSET_H
#define _CC_LOCKSET_H
#include "ace/pre.h"

#include "ace/Synch.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Token.h"
#include "orbsvcs/CosConcurrencyControlS.h"
#include "concurrency_export.h"

#define NUMBER_OF_LOCK_MODES 5
// This constant defines the number of lock modes. There is really no
// way to set this constant dynamically because the nuber of lock
// modes are not stated as part of the IDL.

typedef enum {CC_EM=-1, CC_IR=0, CC_R, CC_U, CC_IW, CC_W} CC_LockModeEnum;
// Enummeration representing the lock modes. The incomming request is
// always converted to this representation. There are two reasons for
// this: Firstly the lock modes are ordered from weakest to strongest
// in the internal representation, and secondly it is possible to
// indicate a 'non-mode' (CC_EM)

class TAO_Concurrency_Export CC_LockSet :  public POA_CosConcurrencyControl::LockSet
{
  // = TITLE
  //     CC_LockSet
  //
  // = DESCRIPTION
  //     This class implements the LockSet interface that is part of
  //     the CosConcurrency service. Please consult the idl file for
  //     detailed descriptions apart from the comments in this file At
  //     present the lock set is not really a set, but only one lock.
public:

  // = Initialization and termination methods.
  CC_LockSet (void);
  // Default constructor

  CC_LockSet (CosConcurrencyControl::LockSet_ptr related);
  // Constructor used if create_related is used to create the lock
  // set.

  ~CC_LockSet (void);
  // Destructor.

  // = CosConcurrencyControl methods
  virtual void lock (CosConcurrencyControl::lock_mode mode,
                     CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // Acquires this lock. Blocks until lock is obtained

  virtual CORBA::Boolean try_lock (CosConcurrencyControl::lock_mode mode,
                                   CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // Tries to acquire this lock. If it is not possible to acquire the
  // lock, false is returned

  virtual void unlock (CosConcurrencyControl::lock_mode mode,
                       CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosConcurrencyControl::LockNotHeld));
  // Releases this lock.

  virtual void change_mode (CosConcurrencyControl::lock_mode held_mode,
                            CosConcurrencyControl::lock_mode new_mode,
                            CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosConcurrencyControl::LockNotHeld));
  // Changes the mode of this lock.

  // = Debugging methods
  void dump (void);
  // Dump the state of the object to stdout

private:
  CC_LockModeEnum lmconvert (CosConcurrencyControl::lock_mode mode);
  // Converts the CORBA specification's lock mode to the internal
  // representation

  void Init (CORBA::Environment &_env);
  // Initiatlizes the lock set array and acquires the initial
  // semaphore.

  CORBA::Boolean compatible (CC_LockModeEnum mr);
  // Returns true if the held lock and the requested lock are compatible

  // The _i functions below ensures atomical access the the state data
  // for the lock set. The functions acquires a thread lock in order
  // to insure consistency within the lock set. The return value
  // typically indicates whether the current thread should be
  // suspended or not (by locking the semaphore.

  int lock_i (CC_LockModeEnum lm);
  // Locks the access to the data and decides whether to lock or
  // not. Returns 1 if the semaphore should be locked.

  // int unlock_i (CosConcurrencyControl::lock_mode lm);
  // This function is not necessary because we lock access to the data
  // and unlocks the semaphore until an invalid lock mode is first on
  // the queue. Thereafter we release the lock.

  int try_lock_i (CC_LockModeEnum lm);
  // Locks the access to the data and determines whether to return
  // true or false. Returns 1 if true should be returned.

  int change_mode_i (CC_LockModeEnum lm_held,
                     CC_LockModeEnum lm_new);
  // Locks access to the data and determines if the semaphore should
  // be locked. Returns 1 if the semaphore should be locked.

  int lock_held (CC_LockModeEnum lm);
  // Locks access ti the data and checks whether the lock is held.

  int lock_[NUMBER_OF_LOCK_MODES];
  // An array of lock counters that counts how many locks of that type
  // that the lock set holds.

  // ACE_Thread_Semaphore semaphore_;
  ACE_Token semaphore_;
  // This is the semaphore for the lock set. The semaphore is used to
  // queue requests for locks in modes stronger than currently
  // possible to grant.  Note that the <ACE_Token> provides strict
  // FIFO ordering of acquisition/release of the lock.

  CosConcurrencyControl::LockSet_ptr related_lockset_;
  // If this lock set is related to another lock set, this is the
  // pointer to the related lock set. This is a really simple
  // solution, but since transactions are not supported in the first
  // version there should be no reason to drop lock sets together. The
  // <LockSetCoordinator> is not implemented (it has the
  // responsibilities of dropping the locks).

  static CORBA::Boolean compatible_[NUMBER_OF_LOCK_MODES][NUMBER_OF_LOCK_MODES];
  // Mapping between requested and held lock modes. Used by compatible
  // (...).  Uses the internal enumeration as indices.

  TAO_SYNCH_MUTEX mlock_;
  // Lock to ensure that race conditions does not occur.

  ACE_Unbounded_Queue <CC_LockModeEnum> lock_queue_;
  // Queue to hold the requested locks not yet granted.
};

#include "ace/post.h"
#endif /* _CC_LOCKSET_H */
