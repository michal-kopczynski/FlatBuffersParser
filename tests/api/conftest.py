import pytest

def pytest_addoption(parser):
    parser.addoption("--port", action="store", default="12345", help="Parser port")

@pytest.fixture
def port(pytestconfig):
    return pytestconfig.option.port
