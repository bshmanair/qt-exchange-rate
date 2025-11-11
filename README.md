# Currency Exchange Rate Converter

## Description

A desktop application built using C++ and Qt Framework that provides real-time currency exchange rates. Convert between different currencies with a simple, intuitive graphical interface powered by ExchangeRate-API.

## Technologies Used

- C++
- Qt Framework
- ExchangeRate-API.com
- CMake

## Features

- Real-time currency exchange rate data
- Simple and intuitive Qt-based GUI
- Convert between multiple international currencies
- Shows conversion 1 unit of source currency to destination currency

## How it works

- User selects source currency and target currency from dropdown menus
- Application sends HTTP request to ExchangeRate-API.com
- API returns current exchange rates in JSON format
- Application displays the conversion result

## Prerequisites

- Qt 5.x or 6.x installed
- Internet connection (for API access)
- ExchangeRate-API key (you can make one [at the official website](https://www.exchangerate-api.com/))

## How to run

WIP

## About the API

This project uses the free tier of [ExchangeRate-API.com](https://www.exchangerate-api.com/)

- Free tier allows up to 1,500 requests per month
- No authentication required for basic usage

## Limitations

- Active internet connection required
- Exchange rates update frequency depends on API plan
- Limited to currencies supported by ExchangeRate-API

## Notes

This project was built to self-learn Qt GUI development and practice API integration in C++

## Contributions

This is a showcase project. Contributions are welcome but not expected.
