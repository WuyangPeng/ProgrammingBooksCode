package com.tcre.weather.test;

import java.io.Serializable;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import java.util.AbstractList;
import java.util.Vector;

import com.tcre.weather.api.StoreException;
import com.tcre.weather.api.RetrieveException;

class PersistentImp implements com.tcre.weather.api.PersistentImp
{
  public void store(String name, Serializable object) throws StoreException
  {
    try
    {
      FileOutputStream f = new FileOutputStream(name);
      ObjectOutputStream s = new ObjectOutputStream(f);
      s.writeObject(object);
    }
    catch(Exception e)
    {
      throw new StoreException();
    }
  }
  
  public Object retrieveObject(String name) throws RetrieveException
  {
    System.out.println("Key : " + name);

    try
    {
       FileInputStream in = new FileInputStream(name);
       ObjectInputStream s = new ObjectInputStream(in);
       Object obj = (Object)s.readObject();
       return obj;
    }
    catch (Exception e)
    {
      throw new RetrieveException();
    }
  }

  public AbstractList directory(String name) throws RetrieveException
  {
    return new Vector();
  }
}
