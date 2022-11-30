package com.tcre;

public interface ShapeFactory
{
  public Shape make(String shapeName) throws Exception;
}
