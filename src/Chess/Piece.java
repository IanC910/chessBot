package Chess;

public class Piece {
    
    private Rules.Colour colour;
    private Rules.PieceType type;

    public Piece(Rules.Colour colour, Rules.PieceType type) {
        this.colour = colour;
        this.type = type;
    }

    public Rules.Colour getColour() {
        return colour;
    }

    public Rules.PieceType getType() {
        return type;
    }
}
