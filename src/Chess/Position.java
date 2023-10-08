package Chess;

public class Position {

    public int rank;
    public int file;

    public Position(int rank, int file) {
        this.rank = rank;
        this.file = file;
    }

    public boolean equals(Position position) {
        return(this.rank == position.rank && this.file == position.file);
    }
}
