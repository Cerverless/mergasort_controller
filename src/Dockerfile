ARG DLESS_TAG=latest

FROM gcc:6 AS build-env
COPY . /app
WORKDIR /app
RUN make -C src

FROM gcr.io/distroless/cc

COPY --from=build-env /app/src/msc /app/
WORKDIR /app
CMD ["./msc]
