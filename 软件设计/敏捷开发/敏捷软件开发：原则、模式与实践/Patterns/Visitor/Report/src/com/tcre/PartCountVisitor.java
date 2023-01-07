package com.tcre;

import java.util.HashMap;

public class PartCountVisitor implements PartVisitor {
    private int itsPieceCount = 0;
    private HashMap itsPieceMap = new HashMap();

    @Override
    public void visit(PiecePart p) {
        itsPieceCount++;
        String partNumber = p.getPartNumber();
        int partNumberCount = 0;
        if (itsPieceMap.containsKey(partNumber)) {
            Integer carrier = (Integer) itsPieceMap.get(partNumber);
            partNumberCount = carrier.intValue();
        }

        partNumberCount++;
        itsPieceMap.put(partNumber, new Integer(partNumberCount));
    }

    @Override
    public void visit(Assembly a) {

    }

    public int getPiectCount() {
        return itsPieceCount;
    }

    public int getPartNumberCount() {
        return itsPieceMap.size();
    }

    public int getCountForPart(String partNumber) {
        int partNumberCount = 0;
        if (itsPieceMap.containsKey(partNumber)) {
            Integer carrier = (Integer) itsPieceMap.get(partNumber);
            partNumberCount = carrier.intValue();
        }
        return partNumberCount;
    }
}
