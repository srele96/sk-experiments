FROM ubuntu:22.04
# Acquire the packages that we need to make the application compile and run.
#
# I should lock the libpq and libpqxx libraries to a specific version. But I
# don't need to do that for the purpose of this sample.
#
# Advice on grouping RUN commands:
# https://stackoverflow.com/questions/39223249/multiple-run-vs-single-chained-run-in-dockerfile-which-is-better
#
# One RUN per dependency to use caching so we don't redownload all dependencies
#  for each change. I don't know if there's a better way to do that.
RUN apt-get update
RUN apt-get install -y curl
RUN apt-get install -y clang
RUN apt-get install -y cmake
RUN apt-get install -y libpq-dev
RUN apt-get install -y libpqxx-dev
WORKDIR /three
COPY . .
RUN chmod +x ./download_include.sh && ./download_include.sh
WORKDIR /three/build
RUN cmake -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_COMPILER=clang++ ..
RUN cmake --build .
EXPOSE 5000
CMD ["./three"]
