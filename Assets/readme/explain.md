# 42-pipex

## Output in file

There is a diffence between > & >>


### overwrite the file's contents

```sh
wc -l > outfile
```

and 

### write the output at the end of the file's contents

```sh
wc -l >> outfile
```

## Example

What the hell is...

```sh
~:$ < infile grep will | wc -l > outfile
```
?

### infile

```
And in a time that's closer, life will be even bolder then
Souls will be complicated, life will be consummated then
Hearts will be brought together soon in our minds forever then

As long as we see there's only us, who can change it
Only us to rearrange it at the start of a new kind of day
```

### grep "will"

```sh
~:$ < infile grep will > outfile
```

### middle outfile

```
And in a time that's closer, life will be even bolder then
Souls will be complicated, life will be consummated then
Hearts will be brought together soon in our minds forever then
```

### copy the outfile in the infile

```
~:$ cp outfile infile
```

### seconde command 

```
~:$ < infile wc -l > outfile
```

### final output

```
3
```
