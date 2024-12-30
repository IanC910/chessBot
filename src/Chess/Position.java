package Chess;

public class Position {

    public static boolean isValid(int rank, int file) {
        return (
            rank >= Board.MIN_RANK &&
            rank <= Board.MAX_RANK &&
            file >= Board.MIN_FILE &&
            file <= Board.MAX_FILE
        );
    }

    public static boolean isValid(Position position) {
        return isValid(position.rank, position.file);
    }

    public final int rank;
    public final int file;

    public Position(int rank, int file) {
        this.rank = rank;
        this.file = file;
    }

    public boolean equals(Position position) {
        return(this.rank == position.rank && this.file == position.file);
    }

    public boolean isValid() {
        return isValid(this.rank, this.file);
    }
}
