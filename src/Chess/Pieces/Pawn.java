package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Move;
import Chess.Position;

public class Pawn extends Piece {
    
    public Pawn(Colour colour) {
        super(colour, 'P', 1);
    }

    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        LinkedList<Move> legalMoves = new LinkedList<>();

        Position startPos = new Position(rank, file);
        
        // Non attacking move
        Position endPos = new Position(
            rank + Board.FORWARD_DIR[this.colour.value],
            file
        );

        Move move = new Move(startPos, this, endPos);

        if(Position.isValid(endPos) && !move.checksOwnKing(board)) {
            if(board.getPiece(endPos).equals(Piece.NO_PIECE)) {
                legalMoves.add(move);
            }
        }

        // Left attacking move
        endPos = new Position(
            rank + Board.FORWARD_DIR[this.colour.value],
            file - 1
        );

        move = new Move(startPos, this, endPos);

        if(Position.isValid(endPos) && !move.checksOwnKing(board)) {
            if(!board.getPiece(endPos).equals(Piece.NO_PIECE) && board.getPiece(endPos).colour != this.colour) {
                legalMoves.add(move);
            }
        }

        // Right attacking move
        endPos = new Position(
            rank + Board.FORWARD_DIR[this.colour.value],
            file + 1
        );

        move = new Move(startPos, this, endPos);

        if(Position.isValid(endPos) && !move.checksOwnKing(board)) {
            if(!board.getPiece(endPos).equals(Piece.NO_PIECE) && board.getPiece(endPos).colour != this.colour) {
                legalMoves.add(move);
            }
        }

        return legalMoves;
    }
}
