ARG VERSION=latest
FROM mhart/alpine-node:${VERSION}

WORKDIR .

COPY . .

RUN node --version

# Install Python dependencies
RUN apk add --update \
    python3  \
    py3-pip \
    build-base \
  && pip3 install virtualenv \
  && rm -rf /var/cache/apk/*

# Build & Test
RUN npm install
RUN npm run build:ts
RUN npm run build
RUN npm run package

# # Publish binary to github
CMD npm run publish:github