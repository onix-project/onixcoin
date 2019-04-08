'use strict'
const express = require('express');
const http = require('http');
const helmet = require('helmet');
const bodyParser = require('body-parser');
const app = express()
              .use(helmet)
              .use(bodyParser.urlencoded({ extended: false }))
              .use(bodyParser.json());

const server = http.createServer(app)
const socket = require('./service/socketBlockchain');
const PORT = process.env.PORT || 23287;

//import { bindControllers, Root, Path } from 'express-router-decorators';


const ws = new socket(server);

//corriendo el servidor
server.listen(PORT, () => {
  console.log(`Server running in http://localhost:${PORT}`); 
})
