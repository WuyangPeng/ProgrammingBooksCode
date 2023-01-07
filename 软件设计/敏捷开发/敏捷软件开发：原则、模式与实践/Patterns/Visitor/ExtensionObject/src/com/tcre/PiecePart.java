package com.tcre;

public class PiecePart extends Part {
    private String itsPartNumber;
    private String itsDescription;
    private double itsCost;

    public PiecePart(String partNumber, String description, double cost) {
        itsPartNumber = partNumber;
        itsDescription = description;
        itsCost = cost;
        addExtension("CSV",new CSVPiecePartExtension(this));
        addExtension("XML",new XMLPiecePartExtension(this));
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
