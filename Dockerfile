ARG VERSION=latest
FROM mhart/alpine-node:${VERSION}

WORKDIR .

COPY . .

RUN node --version

# Install Python dependencies
RUN apk add --update \
    python \
    python-dev \
    py-pip \
    build-base \
  && pip install virtualenv \
  && rm -rf /var/cache/apk/*

# Build & Test
RUN npm install
RUN npm run build:ts
RUN npm run build
RUN npm test

# # Publish binary to github
CMD npm run publish:github
