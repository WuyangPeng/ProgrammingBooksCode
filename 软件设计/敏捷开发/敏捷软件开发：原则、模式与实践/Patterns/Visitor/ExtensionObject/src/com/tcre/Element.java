package com.tcre;

import java.util.ArrayList;
import java.util.List;

public class Element {
    private String name;
    private String text;
    private List<Element> elements = new ArrayList<>();

    public Element(String name) {
        this.name = name;
    }

    public Element setText(String text) {
        this.text = text;
        return this;
    }

    public void addContent(Element content) {
        elements.add(content);
    }

    public String getName() {
        return name;
    }

    public String getTextTrim() {
        return text;
    }

    public Element getChild(String key) {
        for (var value : elements) {
            if (value.name == key) {
                return value;
            }
        }
        return null;
    }

    public List getChildren() {
        return elements;
    }
}
