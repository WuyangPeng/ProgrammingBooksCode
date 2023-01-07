package com.tcre;

public class PiecePart implements Part {
    private String itsPartNumber;
    private String itsDescription;
    private double itsCost;

    public PiecePart(String partNumber, String description, double cost) {
        itsPartNumber = partNumber;
        itsDescription = description;
        itsCost = cost;
    }


    @Override
    public void accept(PartVisitor v) {
        v.visit(this);
    }


    @Override
    public String getPartNumber() {
        return itsPartNumber;
    }

    @Override
    public String getDescription() {
        return itsDescription;
    }

    public double getCost() {
        return itsCost;
    }
}
