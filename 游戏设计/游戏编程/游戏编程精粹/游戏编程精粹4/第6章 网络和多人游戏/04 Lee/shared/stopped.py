"""
stopped.py
"""

import shared
import shared.characterstatedata as _characterstatedata

shared.RegisterState(__name__)

def GetStateId():  
  return _characterstatedata.STOPPED

def GetStateTypeId():
  return _characterstatedata.MOVEMENT

def OnEnterState(actor):
  pass

def OnExitState(actor):
  pass