# fileid
Generic file identifier

Like the linux utility "file", this tool will take an arbirtrary blob and attempt to identify the file type/extension based on magic numbers. In addition it will attempt to pull as much pertinant details as it knows from the file about its format.

usage:
  fileid {file} [format]
    {file} - required path the file in question
    [format] - optional output format (TEXT [default], CSV, JSON, XML)

