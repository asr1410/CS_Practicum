<?php
// Connect to the SQLite database
$database = new SQLite3('/home/runner/testing/my_database.db');

if (!$database) {
    die("Error: Unable to connect to the database");
}

// Fetch data from the tables based on the selected table
$tableName = $_GET['table'] ?? 'unclassified';
$data = $database->query("SELECT * FROM $tableName");

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $id = $_POST['id'];
    $table = $_POST['table'];

    if (in_array($table, ['criminal', 'non_criminal', 'junk'])) {
        $query = "INSERT INTO $table SELECT * FROM $tableName WHERE id = $id";
        $database->exec($query);

        // Delete the row from the unclassified table
        $database->exec("DELETE FROM $tableName WHERE id = $id");
    }

    // Check if the table is 'unclassified', and hide the "Unclassified" button
    if ($table === 'unclassified') {
        $unclassifiedButtonVisible = 'none';
    } else {
        $unclassifiedButtonVisible = 'inline';
    }
} else {
    $unclassifiedButtonVisible = 'none';
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Image Classifier</title>
    <style>
        .container {
            display: flex;
            justify-content: space-between;
        }

        .table-container {
            width: 80%;
            height: 400px; /* Set a fixed height for the table container */
            overflow-y: auto; /* Enable vertical scrolling if needed */
        }

        table {
            border-collapse: collapse;
            width: 100%;
        }

        th, td {
            border: 1px solid #dddddd;
            text-align: left;
            padding: 8px;
        }

        th {
            background-color: #f2f2f2;
        }

        tr:hover {
            background-color: #f5f5f5;
        }

        .image-container {
            flex: 1;
            text-align: center;
            display: none;
            padding-top: 80px;
            max-height: 400px; /* Set a fixed max height for the image container */
        }

        img {
            max-width: 100%;
            max-height: 100%;
        }

        /* Style for classification buttons */
        .classification-button {
            margin: 5px;
            padding: 10px;
            border: none;
            cursor: pointer;
        }

        .criminal-button {
            background-color: red;
            color: white;
        }

        .non-criminal-button {
            background-color: green;
            color: white;
        }

        .junk-button {
            background-color: gray;
            color: white;
        }

        /* Style for the "Unclassified" button */
        .unclassified-button {
            background-color: blue;
            color: white;
            display: <?php echo $unclassifiedButtonVisible; ?>; /* Show or hide the button based on the condition */
        }
    </style>
</head>
<body>
    <h1>Image Classifier</h1>

    <div class="container">
        <div class="table-container">
            <label for="tableSelect">Select Table:</label>
            <select id="tableSelect">
                <option value="unclassified" <?php if ($tableName === 'unclassified') echo 'selected'; ?>>Unclassified</option>
                <option value="criminal" <?php if ($tableName === 'criminal') echo 'selected'; ?>>Criminal</option>
                <option value="non_criminal" <?php if ($tableName === 'non_criminal') echo 'selected'; ?>>Non-Criminal</option>
                <option value="junk" <?php if ($tableName === 'junk') echo 'selected'; ?>>Junk</option>
            </select>

            <table>
                <tr>
                    <th>ID</th>
                    <th>Path</th>
                    <th>X</th>
                    <th>Y</th>
                    <th>Width</th>
                    <th>Height</th>
                </tr>
                <?php while ($row = $data->fetchArray()): ?>
                    <tr>
                        <td><?= $row['id'] ?></td>
                        <td><?= $row['path'] ?></td>
                        <td><?= $row['x'] ?></td>
                        <td><?= $row['y'] ?></td>
                        <td><?= $row['width'] ?></td>
                        <td><?= $row['height'] ?></td>
                    </tr>
                <?php endwhile; ?>
            </table>
        </div>

        <div class="image-container">
            <img id="imageToShow" src="" alt="Image">
            <form method="POST">
                <input type="hidden" id="imageId" name="id" value="">
                <?php if ($tableName === 'unclassified'): ?>
                    <button class="classification-button criminal-button" onclick="classifyImage('criminal')">Criminal</button>
                    <button class="classification-button non-criminal-button" onclick="classifyImage('non_criminal')">Non-Criminal</button>
                    <button class="classification-button junk-button" onclick="classifyImage('junk')">Junk</button>
                <?php endif; ?>
                <!-- "Unclassified" button -->
                <button class="classification-button unclassified-button" onclick="moveToUnclassified()">Unclassified</button>
            </form>
        </div>
    </div>

    <script>
        var imageIdToClassify = "";
        var classificationButtons = document.querySelectorAll('.classification-button');
        var unclassifiedButton = document.querySelector('.unclassified-button');
        var imageContainer = document.querySelector('.image-container');
        var imageToShow = document.getElementById('imageToShow');
        var imageIdField = document.getElementById('imageId');

        function classifyImage(classification) {
            var form = document.querySelector('form');
            imageIdField.value = imageIdToClassify; // Set the image ID to classify
            var input = document.createElement('input');
            input.type = "hidden";
            input.name = "table";
            input.value = classification;
            form.appendChild(input);
            form.submit();
        }

        // Function to move the image back to "Unclassified" table
        function moveToUnclassified() {
            var form = document.querySelector('form');
            var input = document.createElement('input');
            input.type = "hidden";
            input.name = "table";
            input.value = "unclassified";
            form.appendChild(input);
            form.submit();
        }

        document.addEventListener('DOMContentLoaded', function() {
            var rows = document.querySelectorAll('table tr');
            var tableSelect = document.getElementById('tableSelect');

            rows.forEach(function(row) {
                row.addEventListener('click', function() {
                    var pathCell = row.getElementsByTagName('td')[1].textContent;
                    var idCell = row.getElementsByTagName('td')[0].textContent;

                    imageToShow.src = pathCell;
                    imageIdField.value = idCell;
                    imageIdToClassify = idCell; // Set the image ID to classify
                    imageContainer.style.display = 'block';

                    // Show the "Unclassified" button when necessary
                    if (tableSelect.value !== 'unclassified') {
                        unclassifiedButton.style.display = 'inline';
                    }

                    // Enable or disable classification buttons based on the selected table
                    if (tableSelect.value === 'unclassified') {
                        classificationButtons.forEach(function(button) {
                            button.disabled = false;
                        });
                    } else {
                        classificationButtons.forEach(function(button) {
                            button.disabled = true;
                        });
                    }
                });
            });

            tableSelect.addEventListener('change', function() {
                var selectedTable = tableSelect.options[tableSelect.selectedIndex].value;
                location.href = '?table=' + selectedTable;
                imageContainer.style.display = 'none'; // Hide the image when changing the table

                // Hide the "Unclassified" button when switching tables
                unclassifiedButton.style.display = 'none';
            });
        });
    </script>
</body>
</html>