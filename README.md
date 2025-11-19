# GUI for ESGI - Efficient Splitting of Generic Indices

The GUI was developed for MacOS only. Therefore you can only download the pre-build Application only for MacOS or have to download the repository and try to build it for your platform.
The GUI does not integrate STAR and can therefore *demultiplex* and *count* barcoded single-cell data but can not ran STAR with gene-mapping in between.

The GUI builds upon the library of ESGI: [ESGI lib](https://github.com/tstohn/ESGI).

The GUI separetes demultiplexing and counting and the user needs to first *demultiplex* the data and then then subsequently create a single-cell * feature count matrix by running *count*.

Interface for *demultiplex*:
![GUI](https://github.com/tstohn/ESGI-GUI/blob/master/media/demultiplex.png)

Interface for *count*:
